#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityLibrary.h"
#include "TsubasamusuEditorUtilityLibrary.generated.h"

UCLASS()
class TSUBASAMUSUUNREALEDITOR_API UTsubasamusuEditorUtilityLibrary : public UEditorUtilityLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "TSUBASAMUSU|EditorUtility")
	static UMaterialInstance* CreateMaterialInstanceAsset(UMaterialInstanceDynamic* SourceMaterialInstanceDynamic, const FString& CreateDirectory);

	UFUNCTION(BlueprintCallable, Category = "TSUBASAMUSU|EditorUtility")
	static void ReplaceReferences(UObject* OldAsset, UObject* NewAsset);

private:
	static bool SavePackage(UPackage* Package, UObject* Asset, const FString& FileName);
};