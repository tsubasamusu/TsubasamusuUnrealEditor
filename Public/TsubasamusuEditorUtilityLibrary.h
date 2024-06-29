#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityLibrary.h"
#include "TsubasamusuEditorUtilityLibrary.generated.h"

UCLASS()
class TSUBASAMUSUUNREALEDITOR_API UTsubasamusuEditorUtilityLibrary : public UEditorUtilityLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "TSUBASAMUSU|EditorUtility", meta = (KeyWords = "create material instance asset"))
	static UMaterialInstance* CreateMaterialInstanceAsset(const UMaterialInstanceDynamic* SourceMaterialInstanceDynamic, FString CreateDirectory);
};