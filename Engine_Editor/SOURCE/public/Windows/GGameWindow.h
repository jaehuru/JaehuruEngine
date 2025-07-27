#pragma once

#include "GEditorWindow.h"

class GEditor;

class GGameWindow : public GEditorWindow
{
public:
	GGameWindow();
	~GGameWindow();

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

