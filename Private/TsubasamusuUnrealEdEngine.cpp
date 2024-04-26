#include "TsubasamusuUnrealEdEngine.h"
#include "Settings/EditorStyleSettings.h"
#include "GraphEditorSettings.h"
#include "InternationalizationSettingsModel.h"
#include "Internationalization/CulturePointer.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"

void UTsubasamusuUnrealEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);

	SetupEditorSettings();
}

void UTsubasamusuUnrealEdEngine::SetupEditorSettings()
{
	GetMutableDefault<UEditorLoadingSavingSettings>()->bAutoSaveEnable = false;

	GetMutableDefault<UEditorStyleSettings>()->AssetEditorOpenLocation = EAssetEditorOpenLocation::MainWindow;

	SetupCommentSettings();

	SetupRegionAndLanguageSettings();
}

void UTsubasamusuUnrealEdEngine::SetupCommentSettings()
{
	UGraphEditorSettings* GraphEditorSettings = GetMutableDefault<UGraphEditorSettings>();

	GraphEditorSettings->bShowCommentBubbleWhenZoomedOut = true;

	GraphEditorSettings->DefaultCommentNodeTitleColor = FLinearColor::Black;
}

void UTsubasamusuUnrealEdEngine::SetupRegionAndLanguageSettings()
{
	TWeakObjectPtr<UInternationalizationSettingsModel> InternationalizationSettingsModel = GetMutableDefault<UInternationalizationSettingsModel>();

	{
		FInternationalization* Internationalization = &FInternationalization::Get();

		FCulturePtr CulturePtr = Internationalization->GetCulture(TEXT("en"));

		InternationalizationSettingsModel->SetEditorLanguage(CulturePtr->GetName());

		InternationalizationSettingsModel->SetEditorLocale(CulturePtr->GetName());
	}

	InternationalizationSettingsModel->SetShouldUseLocalizedNodeAndPinNames(false);

	InternationalizationSettingsModel->SetShouldUseLocalizedNumericInput(false);

	InternationalizationSettingsModel->SetShouldUseLocalizedPropertyNames(false);
}