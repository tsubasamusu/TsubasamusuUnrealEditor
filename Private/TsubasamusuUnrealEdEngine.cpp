#include "TsubasamusuUnrealEdEngine.h"
#include "Settings/EditorStyleSettings.h"
#include "GraphEditorSettings.h"

void UTsubasamusuUnrealEdEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);

	SetupEditorSettings();
}

void UTsubasamusuUnrealEdEngine::SetupEditorSettings()
{
	//自動保存を無効化
	GetMutableDefault<UEditorLoadingSavingSettings>()->bAutoSaveEnable = false;

	//アセットエディタをメインウィンドウで開くように設定
	GetMutableDefault<UEditorStyleSettings>()->AssetEditorOpenLocation = EAssetEditorOpenLocation::MainWindow;

	{
		UGraphEditorSettings* GraphEditorSettings = GetMutableDefault<UGraphEditorSettings>();

		//ズームアウト時にコメントの吹き出しを表示するように設定
		GraphEditorSettings->bShowCommentBubbleWhenZoomedOut = true;

		//コメントの初期色を黒色に設定
		GraphEditorSettings->DefaultCommentNodeTitleColor = FLinearColor::Black;
	}
}