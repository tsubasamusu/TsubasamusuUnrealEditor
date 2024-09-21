#include "TsubasamusuEditorUtilityLibrary.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetDeleteModel.h"
#include "AssetRegistry/AssetRegistryHelpers.h"
#include "UObject/SavePackage.h"

UMaterialInstance* UTsubasamusuEditorUtilityLibrary::CreateMaterialInstanceAsset(const UMaterialInstanceDynamic* SourceMaterialInstanceDynamic, const FString CreateDirectory)
{
    if (!IsValid(SourceMaterialInstanceDynamic))
    {
        UE_LOG(LogTemp, Error, TEXT("The \"SourceMaterialInstanceDynamic\" is not valid."));

        return nullptr;
    }

    if (!CreateDirectory.StartsWith(TEXT("/Game/")))
    {
        UE_LOG(LogTemp, Error, TEXT("The \"CreateDirectory\" does not start with \"/Game/\". The entered value is \"%s\"."), *CreateDirectory);

        return nullptr;
    }

    FString FinalDirectory = FPaths::Combine(CreateDirectory, SourceMaterialInstanceDynamic->GetName());

    if (IsValid(StaticLoadObject(UObject::StaticClass(), nullptr, *FinalDirectory)))
    {
        UE_LOG(LogTemp, Error, TEXT("\"%s\" already exists."), *FinalDirectory);

        return nullptr;
    }

    UPackage* Package = CreatePackage(*FinalDirectory);

    if (!IsValid(Package))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create a Package named \"%s\"."), *SourceMaterialInstanceDynamic->GetName());

        return nullptr;
    }

    UMaterialInstanceConstant* MaterialInstanceConstant = NewObject<UMaterialInstanceConstant>(Package, FName(*SourceMaterialInstanceDynamic->GetName()), RF_Public | RF_Standalone);

    if (!IsValid(MaterialInstanceConstant))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create a UMaterialInstanceConstant based on \"%s\"."), *SourceMaterialInstanceDynamic->GetName());

        return nullptr;
    }

    MaterialInstanceConstant->SetParentEditorOnly(SourceMaterialInstanceDynamic->Parent);

    MaterialInstanceConstant->ScalarParameterValues = SourceMaterialInstanceDynamic->ScalarParameterValues;
    MaterialInstanceConstant->VectorParameterValues = SourceMaterialInstanceDynamic->VectorParameterValues;
    MaterialInstanceConstant->TextureParameterValues = SourceMaterialInstanceDynamic->TextureParameterValues;

    FAssetRegistryModule::AssetCreated(MaterialInstanceConstant);

    MaterialInstanceConstant->MarkPackageDirty();

    FSavePackageArgs SavePackageArgs;

    SavePackageArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;

    SavePackageArgs.Error = GError;

    SavePackageArgs.bForceByteSwapping = true;

    SavePackageArgs.SaveFlags = SAVE_NoError;

    const bool bSaved = UPackage::SavePackage(Package, MaterialInstanceConstant, *FPackageName::LongPackageNameToFilename(FinalDirectory, FPackageName::GetAssetPackageExtension()), SavePackageArgs);

    if (bSaved) return Cast<UMaterialInstance>(MaterialInstanceConstant);

    UE_LOG(LogTemp, Error, TEXT("Failed to save the created Package based on \"%s\"."), *SourceMaterialInstanceDynamic->GetName());

    return nullptr;
}

void UTsubasamusuEditorUtilityLibrary::ReplaceReferences(UObject* OldAsset, UObject* NewAsset)
{
    if (!IsValid(OldAsset))
    {
        UE_LOG(LogTemp, Error, TEXT("The \"OldAsset\" is not valid."));

        return;
    }

    if (!IsValid(NewAsset))
    {
        UE_LOG(LogTemp, Error, TEXT("The \"NewAsset\" is not valid."));

        return;
    }

    float ScanSpan = 0.1f;

    TSharedPtr<FAssetDeleteModel> AssetDeleteModel = MakeShared<FAssetDeleteModel>(TArray<UObject*>({ OldAsset }));

    TSharedPtr<FAssetData> NewAssetData = MakeShared<FAssetData>(NewAsset);

    AssetDeleteModel->OnStateChanged().AddLambda([AssetDeleteModel, ScanSpan, NewAssetData](FAssetDeleteModel::EState NewState)
        {
            if (NewState != FAssetDeleteModel::EState::Finished)
            {
                AssetDeleteModel->Tick(ScanSpan);

                return;
            }

            bool bSuccess = AssetDeleteModel->DoReplaceReferences(*NewAssetData);

            if (!bSuccess) UE_LOG(LogTemp, Error, TEXT("Failed to replace references to \"%s\"."), *NewAssetData->GetAsset()->GetName());
        });

    AssetDeleteModel->Tick(ScanSpan);
}