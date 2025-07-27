#pragma once

#include "GEditorWindow.h"

class GEditor;

class GConsoleWindow : public GEditorWindow
{
public:
	GConsoleWindow();
	~GConsoleWindow();

	void Initialize() override;
	void Update() override;
	void OnGUI() override;
	void Run() override;
	void OnEnable() override;
	void OnDisable() override;
	void OnDestroy() override;

private:
	vector<GEditor*> mEditors;
};