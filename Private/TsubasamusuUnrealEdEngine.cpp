#include "TsubasamusuUnrealEdEngine.h"
#include "Settings/EditorStyleSettings.h"
#include "GraphEditorSettings.h"
#include "InternationalizationSettingsModel.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"

void UTsubasamusuUnrealEdEngine::Init(IEngineLoop* InEngineLoop)
{
    Super::Init(InEngineLoop);

    SetupEditorSettings();
}

void UTsubasamusuUnrealEdEngine::SetupEditorSettings()
{
    UEditorLoadingSavingSettings* EditorSettings = GetMutableDefault<UEditorLoadingSavingSettings>();

    EditorSettings->bAutoSaveEnable = false;

    UEditorStyleSettings* StyleSettings = GetMutableDefault<UEditorStyleSettings>();

    StyleSettings->AssetEditorOpenLocation = EAssetEditorOpenLocation::MainWindow;

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
    UInternationalizationSettingsModel* InternationalizationSettingsModel = GetMutableDefault<UInternationalizationSettingsModel>();

    FInternationalization& Internationalization = FInternationalization::Get();

    FCulturePtr CulturePtr = Internationalization.GetCulture(TEXT("en"));

    if (!CulturePtr.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to retrieve culture for 'en'."));

        return;
    }

    InternationalizationSettingsModel->SetEditorLanguage(CulturePtr->GetName());
    InternationalizationSettingsModel->SetEditorLocale(CulturePtr->GetName());
    InternationalizationSettingsModel->SetShouldUseLocalizedNodeAndPinNames(false);
    InternationalizationSettingsModel->SetShouldUseLocalizedNumericInput(false);
    InternationalizationSettingsModel->SetShouldUseLocalizedPropertyNames(false);
}