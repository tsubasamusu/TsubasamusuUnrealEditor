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
	//�����ۑ��𖳌���
	GetMutableDefault<UEditorLoadingSavingSettings>()->bAutoSaveEnable = false;

	//�A�Z�b�g�G�f�B�^�����C���E�B���h�E�ŊJ���悤�ɐݒ�
	GetMutableDefault<UEditorStyleSettings>()->AssetEditorOpenLocation = EAssetEditorOpenLocation::MainWindow;

	{
		UGraphEditorSettings* GraphEditorSettings = GetMutableDefault<UGraphEditorSettings>();

		//�Y�[���A�E�g���ɃR�����g�̐����o����\������悤�ɐݒ�
		GraphEditorSettings->bShowCommentBubbleWhenZoomedOut = true;

		//�R�����g�̏����F�����F�ɐݒ�
		GraphEditorSettings->DefaultCommentNodeTitleColor = FLinearColor::Black;
	}
}