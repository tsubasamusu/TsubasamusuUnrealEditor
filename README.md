# 機能
## エディタ設定の自動化
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
# EditorUtility で使用可能なノード
## MaterialInstanceDynamic を基にして MaterialInstance のアセットを作成する

<img width="500" src="https://github.com/user-attachments/assets/c450cfae-9da5-4bca-83d2-4106a2666e56">

## ``OldAsset`` の参照を ``NewAsset`` に置換する

<img width="500" src="https://github.com/user-attachments/assets/af7a7331-6681-41fe-baa4-f598877c3aca">

# 使用方法
## ソースコードのインポート
### 手順1
「Releases」から最新版（Latest）の「Source code」をダウンロードする。
### 手順2
ダウンロードした ZIP ファイルを展開して UE プロジェクトのルートディレクトリにある「Source」フォルダ内に移動させる。
## コーディング
### 手順3
「{プロジェクト名}Editor.Target.cs」に ``ExtraModuleNames.Add("TsubasamusuUnrealEditor");`` を追加する。
### 手順4
UE プロジェクトの「.uproject」ファイル内の ``Modules``に以下のコードを追加する。
```json
{
	"Name": "TsubasamusuUnrealEditor",
	"Type": "Editor",
	"LoadingPhase": "Default"
}
```
### 手順5
UE プロジェクトのルートディレクトリにある「Config」フォルダの「DefaultEngine.ini」に以下のコードを追加する。
```
[/Script/Engine.Engine]
UnrealEdEngine=/Script/TsubasamusuUnrealEditor.TsubasamusuUnrealEdEngine
```
## デバッグ
### 手順6
UE エディタを閉じている状態でビルドし、ビルド完了後に UE エディタを開く。
### 手順7
「Edit ＞ Editor Preferences...」で該当設定が変わっている事を確認する。