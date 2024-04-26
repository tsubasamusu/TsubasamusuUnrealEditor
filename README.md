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
# 使用方法
## ソースコードのインポート
### 手順1