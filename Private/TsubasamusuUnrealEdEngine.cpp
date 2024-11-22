#include "TsubasamusuUnrealEdEngine.h"
#include "Settings/EditorStyleSettings.h"
#include "GraphEditorSettings.h"
#include "InternationalizationSettingsModel.h"
#include "Internationalization/Culture.h"

void UTsubasamusuUnrealEdEngine::Init(IEngineLoop* InEngineLoop)
{
    Super::Init(InEngineLoop);

    SetupEditorLoadingSavingSettings();
    SetupEditorStyleSettings();
    SetupGraphEditorSettings();
    SetupInternationalizationSettings();
}

void UTsubasamusuUnrealEdEngine::SetupEditorLoadingSavingSettings()
{
    UEditorLoadingSavingSettings* EditorLoadingSavingSettings = GetMutableDefault<UEditorLoadingSavingSettings>();

    EditorLoadingSavingSettings->bAutoSaveEnable = false;
}

void UTsubasamusuUnrealEdEngine::SetupEditorStyleSettings()
{
    UEditorStyleSettings* EditorStyleSettings = GetMutableDefault<UEditorStyleSettings>();

    EditorStyleSettings->AssetEditorOpenLocation = EAssetEditorOpenLocation::MainWindow;
}

void UTsubasamusuUnrealEdEngine::SetupGraphEditorSettings()
{
    UGraphEditorSettings* GraphEditorSettings = GetMutableDefault<UGraphEditorSettings>();

    GraphEditorSettings->bShowCommentBubbleWhenZoomedOut = true;

    GraphEditorSettings->DefaultCommentNodeTitleColor = FLinearColor::Black;
}

void UTsubasamusuUnrealEdEngine::SetupInternationalizationSettings()
{
    UInternationalizationSettingsModel* InternationalizationSettingsModel = GetMutableDefault<UInternationalizationSettingsModel>();

    //FInternationalization& Internationalization = FInternationalization::Get();

    //FCulturePtr EnglishCulturePtr = Internationalization.GetCulture(TEXT("en"));

    //InternationalizationSettingsModel->SetEditorLanguage(EnglishCulturePtr->GetName());
    //InternationalizationSettingsModel->SetEditorLocale(EnglishCulturePtr->GetName());
    InternationalizationSettingsModel->SetShouldUseLocalizedNodeAndPinNames(false);
    InternationalizationSettingsModel->SetShouldUseLocalizedNumericInput(false);
    InternationalizationSettingsModel->SetShouldUseLocalizedPropertyNames(false);
}