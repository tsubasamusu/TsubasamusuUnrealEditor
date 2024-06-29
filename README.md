# 機能
## エディタ設定の自動化
以下の設定項目を自動で変更します。
好みに合わない設定がある場合は ``UTsubasamusuUnrealEdEngine::SetupEditorSettings()`` を編集して頂ければと思います。

- General
	- Appearance
		- User Interface
			- **_Asset Editor Open Location_**：**_Main Window_**
	- Loading & Saving
		- Auto Save
			- **_Enable AutoSave_**：**_false_**
	- Region & Language
		- Internationalization
			- **_Editor Language_**：**_English_**
			- **_Editpr Locale_**：**_English_**
			- **_Use Localized Numeric Input_**：**_false_**
			- **_Use Localized Property Names_**：**_false_**
			- **_Use Localized Graph Editor Node and Pin Names_**：**_false_**
- Content Editors
	- Graph Editors
		- Node Title Colors
			- **_Default Comment Node Title Color_**：**_black_**
		- Comment Nodes
			- **_Show Comment Bubble when Zoomed Out_**：**_true_**
## マテリアルインスタンスダイナミックを基にしたマテリアルインスタンスのアセットの作成
![スクリーンショット 2024-06-30 065628](https://github.com/tsubasamusu/TsubasamusuUnrealEditor/assets/106749709/5f5ce97f-a6e6-4e6e-91f3-ac9bd0165a89)
# 使用方法
## ソースコードのインポート
### 手順1
「**Releases**」から最新版（**Latest**）の「**Source code**」をダウンロードする。
### 手順2
ダウンロードした ZIP ファイルを展開して UE プロジェクトのルートディレクトリにある「**Source**」フォルダ内に移動させる。
## コーディング
### 手順3
「**{プロジェクト名}Editor.Target.cs**」に ``ExtraModuleNames.Add("TsubasamusuUnrealEditor");`` を追加する。
### 手順4
UE プロジェクトの「**.uproject**」ファイル内の「**Modules**」に以下のコードを追加する。
```json
{
	"Name": "TsubasamusuUnrealEditor",
	"Type": "Editor",
	"LoadingPhase": "Default"
}
```
### 手順5
UE プロジェクトのルートディレクトリにある「**Config**」フォルダの「**DefaultEngine.ini**」に以下のコードを追加する。
```
[/Script/Engine.Engine]
UnrealEdEngine=/Script/TsubasamusuUnrealEditor.TsubasamusuUnrealEdEngine
```
## デバッグ
### 手順6
UE エディタを閉じている状態でビルドし、ビルド完了後に UE エディタを開く。
### 手順7
「**Edit** ＞ **Editor Preferences...**」で該当設定が変わっている事を確認する。
