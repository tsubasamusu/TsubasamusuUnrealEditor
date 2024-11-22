#include "TsubasamusuEditorUtilityLibrary.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetDeleteModel.h"
#include "AssetRegistry/AssetRegistryHelpers.h"
#include "UObject/SavePackage.h"

DEFINE_LOG_CATEGORY_STATIC(LogTsubasamusuUnrealEditor, Error, All);

UMaterialInstance* UTsubasamusuEditorUtilityLibrary::CreateMaterialInstanceAsset(UMaterialInstanceDynamic* SourceMaterialInstanceDynamic, const FString& CreateDirectory)
{
    if (!IsValid(SourceMaterialInstanceDynamic))
    {
        UE_LOG(LogTsubasamusuUnrealEditor, Error, TEXT("Creating a MaterialInstance asset failed because the MaterialInstanceDynamic is not valid."));

        return nullptr;
    }

    if (!CreateDirectory.StartsWith(TEXT("/Game/")))
    {
        UE_LOG(LogTsubasamusuUnrealEditor, Error, TEXT("Creating a MaterialInstance asset failed because the directory string does not start with \"/Game/\"."));

        return nullptr;
    }

    FString AssetPath = CreateDirectory / SourceMaterialInstanceDynamic->GetName();

    if(AssetPath.Contains(TEXT("//"))) AssetPath.ReplaceInline(TEXT("//"), TEXT("/"));

    UPackage* Package = CreatePackage(*AssetPath);

    if (!IsValid(Package))
    {
        UE_LOG(LogTsubasamusuUnrealEditor, Error, TEXT("Creating a MaterialInstance asset failed because creating a Package of \"%s\" failed."), *AssetPath);

        return nullptr;
    }

    UMaterialInstanceConstant* MaterialInstanceConstant = NewObject<UMaterialInstanceConstant>(Package, FName(*SourceMaterialInstanceDynamic->GetName()), RF_Public | RF_Standalone);

    if (!IsValid(MaterialInstanceConstant))
    {
        UE_LOG(LogTsubasamusuUnrealEditor, Error, TEXT("Creating a MaterialInstance asset failed because creating a MaterialInstanceConstant of \"%s\" failed."), *AssetPath);

        return nullptr;
    }

    MaterialInstanceConstant->SetParentEditorOnly(SourceMaterialInstanceDynamic->Parent);
    MaterialInstanceConstant->ScalarParameterValues = SourceMaterialInstanceDynamic->ScalarParameterValues;
    MaterialInstanceConstant->VectorParameterValues = SourceMaterialInstanceDynamic->VectorParameterValues;
    MaterialInstanceConstant->TextureParameterValues = SourceMaterialInstanceDynamic->TextureParameterValues;

    FAssetRegistryModule::AssetCreated(MaterialInstanceConstant);

    MaterialInstanceConstant->MarkPackageDirty();

    FString FileName = FPackageName::LongPackageNameToFilename(AssetPath, FPackageName::GetAssetPackageExtension());

    bool bSaved = SavePackage(Package, MaterialInstanceConstant, FileName);

    if (!bSaved)
    {
        UE_LOG(LogTsubasamusuUnrealEditor, Error, TEXT("Creating a MaterialInstance asset failed because saving a Package of \"%s\" failed."), *AssetPath);

        return nullptr;
    }

    UMaterialInstance* CreatedMaterialInstance = Cast<UMaterialInstance>(MaterialInstanceConstant);

    if (!IsValid(CreatedMaterialInstance))
    {
        UE_LOG(LogTsubasamusuUnrealEditor, Error, TEXT("Creating a MaterialInstance asset failed because the created MaterialInstance is not valid."));

        return nullptr;
    }

    return CreatedMaterialInstance;
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

bool UTsubasamusuEditorUtilityLibrary::SavePackage(UPackage* Package, UObject* Asset, const FString& FileName)
{
    FSavePackageArgs SavePackageArgs;

    SavePackageArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
    SavePackageArgs.Error = GError;
    SavePackageArgs.bForceByteSwapping = true;
    SavePackageArgs.SaveFlags = SAVE_NoError;

    return UPackage::SavePackage(Package, Asset, *FileName, SavePackageArgs);
}