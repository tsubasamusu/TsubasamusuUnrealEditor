#include "TsubasamusuEditorUtilityLibrary.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetDeleteModel.h"
#include "AssetRegistry/AssetRegistryHelpers.h"

UMaterialInstance* UTsubasamusuEditorUtilityLibrary::CreateMaterialInstanceAsset(const UMaterialInstanceDynamic* SourceMaterialInstanceDynamic, const FString& CreateDirectory)
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

    TUniquePtr<FString> CreateDirectoryPtr = MakeUnique<FString>(CreateDirectory);

    if (!CreateDirectoryPtr->EndsWith(TEXT("/"))) CreateDirectoryPtr->Append(TEXT("/"));

    CreateDirectoryPtr->Append(SourceMaterialInstanceDynamic->GetName());

    if (IsValid(StaticLoadObject(UObject::StaticClass(), nullptr, **CreateDirectoryPtr)))
    {
        UE_LOG(LogTemp, Error, TEXT("\"%s\" already exists."), **CreateDirectoryPtr);

        return nullptr;
    }

    TObjectPtr<UPackage> Package = CreatePackage(**CreateDirectoryPtr);

    if (!IsValid(Package))
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create a Package named \"%s\"."), *SourceMaterialInstanceDynamic->GetName());
    
        return nullptr;
    }

    TUniquePtr<FString> MaterialInstanceName = MakeUnique<FString>(SourceMaterialInstanceDynamic->GetName());

    TObjectPtr<UMaterialInstanceConstant> MaterialInstanceConstant = NewObject<UMaterialInstanceConstant>(Package, FName(**MaterialInstanceName), RF_Public | RF_Standalone);

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

    TUniquePtr<bool> bSaved = MakeUnique<bool>(UPackage::SavePackage(Package, MaterialInstanceConstant, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *FPackageName::LongPackageNameToFilename(*CreateDirectoryPtr, FPackageName::GetAssetPackageExtension())));

    if (bSaved.IsValid() && *bSaved) return Cast<UMaterialInstance>(MaterialInstanceConstant);

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

    const TSharedRef<float> ScanSpan = MakeShared<float>(0.1f);

    TSharedRef<FAssetDeleteModel> AssetDeleteModel = MakeShared<FAssetDeleteModel>((TArray<UObject*>({ OldAsset })));

    TSharedRef<FAssetData> NewAssetData = MakeShared<FAssetData>(NewAsset);

    AssetDeleteModel->OnStateChanged().AddLambda([AssetDeleteModel, ScanSpan, NewAssetData](FAssetDeleteModel::EState NewState)
        {
            AssetDeleteModel->Tick(*ScanSpan);

            if (NewState != FAssetDeleteModel::EState::Finished) return;

            //if (!AssetDeleteModel->CanReplaceReferencesWith(*NewAssetData)) return;

            const TUniquePtr<bool> bSuccess = MakeUnique<bool>(AssetDeleteModel->DoReplaceReferences(*NewAssetData));

            if (!bSuccess.IsValid() || !*bSuccess) UE_LOG(LogTemp, Error, TEXT("Failed to replace references to \"%s\"."), *NewAssetData->GetAsset()->GetName());
        });

    AssetDeleteModel->Tick(*ScanSpan);
}