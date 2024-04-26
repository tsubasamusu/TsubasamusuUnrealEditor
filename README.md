# �@�\
## �G�f�B�^�ݒ�̎�����
�ȉ��̐ݒ荀�ڂ������ŕύX���܂��B
�D�݂ɍ���Ȃ��ݒ肪����ꍇ�� ``UTsubasamusuUnrealEdEngine::SetupEditorSettings()`` ��ҏW���Ē�����΂Ǝv���܂��B

- General
	- Appearance
		- User Interface
			- **_Asset Editor Open Location_**�F**_Main Window_**
	- Loading & Saving
		- Auto Save
			- **_Enable AutoSave_**�F**_false_**
	- Region & Language
		- Internationalization
			- **_Editor Language_**�F**_English_**
			- **_Editpr Locale_**�F**_English_**
			- **_Use Localized Numeric Input_**�F**_false_**
			- **_Use Localized Property Names_**�F**_false_**
			- **_Use Localized Graph Editor Node and Pin Names_**�F**_false_**
- Content Editors
	- Graph Editors
		- Node Title Colors
			- **_Default Comment Node Title Color_**�F**_black_**
		- Comment Nodes
			- **_Show Comment Bubble when Zoomed Out_**�F**_true_**
# �g�p���@
## �\�[�X�R�[�h�̃C���|�[�g
### �菇1
�u**Releases**�v����ŐV�Łi**Latest**�j�́u**Source code**�v���_�E�����[�h����B
### �菇2
�_�E�����[�h���� ZIP �t�@�C����W�J���� UE �v���W�F�N�g�̃��[�g�f�B���N�g���ɂ���u**Source**�v�t�H���_���Ɉړ�������B
## �R�[�f�B���O
### �菇3
�u**{�v���W�F�N�g��}Editor.Target.cs**�v�� ``ExtraModuleNames.Add("TsubasamusuUnrealEditor");`` ��ǉ�����B
### �菇4
UE �v���W�F�N�g�́u**.uproject**�v�t�@�C�����́u**Modules**�v�Ɉȉ��̃R�[�h��ǉ�����B
```json
{
	"Name": "TsubasamusuUnrealEditor",
	"Type": "Editor",
	"LoadingPhase": "Default"
}
```
## �f�o�b�O
### �菇5
UE �G�f�B�^����Ă����ԂŃr���h���A�r���h������� UE �G�f�B�^���J���B
### �菇6
�u**Edit** �� **Editor Preferences...**�v�ŊY���ݒ肪�ς���Ă��鎖���m�F����B