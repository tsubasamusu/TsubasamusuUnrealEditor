#pragma once

#include "CoreMinimal.h"
#include "Editor/UnrealEdEngine.h"
#include "TsubasamusuUnrealEdEngine.generated.h"

UCLASS()
class TSUBASAMUSUUNREALEDITOR_API UTsubasamusuUnrealEdEngine : public UUnrealEdEngine
{
	GENERATED_BODY()

public:
	void Init(IEngineLoop* InEngineLoop) override;

private:
	void SetupEditorSettings();
	void SetupCommentSettings();
	void SetupRegionAndLanguageSettings();
};