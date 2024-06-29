#include "TsubasamusuEditorUtilityLibrary.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetDeleteModel.h"
#include "AssetRegistry/AssetRegistryHelpers.h"

UMaterialInstance* UTsubasamusuEditorUtilityLibrary::CreateMaterialInstanceAsset(const UMaterialInstanceDynamic* SourceMaterialInstanceDynamic, FString CreateDirectory)
{
    if (SourceMaterialInstanceDynamic == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("The \"SourceMaterialInstanceDynamic\" is nullptr."));

        return nullptr;
    }

    if (!CreateDirectory.StartsWith(TEXT("/Game/")))
    {
        UE_LOG(LogTemp, Error, TEXT("The \"CreateDirectory\" does not start with \"/Game/\". The value of \"CreateDirectory\" is \"%s\"."), *CreateDirectory);

        return nullptr;
    }

    if (!CreateDirectory.EndsWith(TEXT("/"))) CreateDirectory.Append(TEXT("/"));

    CreateDirectory.Append(SourceMaterialInstanceDynamic->GetName());

    if (StaticLoadObject(UObject::StaticClass(), nullptr, *CreateDirectory) != nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("\"%s\" already exists."), *CreateDirectory);

        return nullptr;
    }

    UPackage* Package = CreatePackage(*CreateDirectory);

    if (Package == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create a Package named \"%s\"."), *SourceMaterialInstanceDynamic->GetName());

        return nullptr;
    }

    FString MaterialInstanceName = SourceMaterialInstanceDynamic->GetName();

    UMaterialInstanceConstant* MaterialInstanceConstant = NewObject<UMaterialInstanceConstant>(Package, FName(*MaterialInstanceName), RF_Public | RF_Standalone);

    if (MaterialInstanceConstant == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create a MaterialInstanceConstant based on \"%s\"."), *SourceMaterialInstanceDynamic->GetName());

        return nullptr;
    }

    MaterialInstanceConstant->SetParentEditorOnly(SourceMaterialInstanceDynamic->Parent);

    MaterialInstanceConstant->ScalarParameterValues = SourceMaterialInstanceDynamic->ScalarParameterValues;
    MaterialInstanceConstant->VectorParameterValues = SourceMaterialInstanceDynamic->VectorParameterValues;
    MaterialInstanceConstant->TextureParameterValues = SourceMaterialInstanceDynamic->TextureParameterValues;

    FAssetRegistryModule::AssetCreated(MaterialInstanceConstant);

    MaterialInstanceConstant->MarkPackageDirty();

    bool bSaved = UPackage::SavePackage(Package, MaterialInstanceConstant, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *FPackageName::LongPackageNameToFilename(CreateDirectory, FPackageName::GetAssetPackageExtension()));

    if (bSaved) return Cast<UMaterialInstance>(MaterialInstanceConstant);

    UE_LOG(LogTemp, Error, TEXT("Failed to save the created Package based on \"%s\"."), *SourceMaterialInstanceDynamic->GetName());

    return nullptr;
}

void UTsubasamusuEditorUtilityLibrary::ReplaceReferences(UObject* OldAsset, UObject* NewAsset)
{
    if (OldAsset == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("The \"OldAsset\" is nullptr."));

        return;
    }

    if (NewAsset == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("The \"NewAsset\" is nullptr."));

        return;
    }

    TSharedPtr<FAssetDeleteModel> AssetDeleteModel = MakeShareable(new FAssetDeleteModel(TArray<UObject*>({ OldAsset })));

    FAssetData NewAssetData(NewAsset);

    AssetDeleteModel->OnStateChanged().AddLambda([AssetDeleteModel, NewAssetData](FAssetDeleteModel::EState NewState)
        {
            AssetDeleteModel->Tick(0.1f);

            if (NewState != FAssetDeleteModel::EState::Finished) return;

            /*if (!AssetDeleteModel->CanReplaceReferencesWith(NewAssetData))
            {
                UE_LOG(LogTemp, Error, TEXT("You cannot replace references to \"%s\"."), *NewAssetData.GetAsset()->GetName());

                return;
            }*/

            bool bSuccess = AssetDeleteModel->DoReplaceReferences(NewAssetData);

            if (!bSuccess) UE_LOG(LogTemp, Error, TEXT("Failed to replace references to \"%s\"."), *NewAssetData.GetAsset()->GetName());
        });

    //Scan again after a certain time.
    AssetDeleteModel->Tick(0.1f);
}