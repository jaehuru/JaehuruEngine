#include "Windows/GGameWindow.h"
#include "Editor/GEditor.h"


GGameWindow::GGameWindow()
{
	SetName("Game");
	SetSize(ImVec2(300, 600));
}

GGameWindow::~GGameWindow()
{

}

void GGameWindow::Initialize()
{

}

void GGameWindow::Update()
{
	for (GEditor* editor : mEditors)
	{
		editor->Update();
	}
}

void GGameWindow::OnGUI()
{
	for (GEditor* editor : mEditors)
	{
		editor->OnGUI();
	}
}

void GGameWindow::Run()
{
	bool Active = (bool)GetState();
	ImGui::Begin(GetName().c_str(), &Active, GetFlag());

	Update();
	OnGUI();

	ImGui::End();
}

void GGameWindow::OnEnable()
{

}

void GGameWindow::OnDisable()
{

}

void GGameWindow::OnDestroy()
{

}
