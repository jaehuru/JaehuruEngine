#include "Windows/GConsoleWindow.h"
#include "Editor/GEditor.h"

GConsoleWindow::GConsoleWindow()
{
	SetName("Console");
	SetSize(ImVec2(300, 600));
}

GConsoleWindow::~GConsoleWindow()
{

}

void GConsoleWindow::Initialize()
{

}

void GConsoleWindow::Update()
{
	for (GEditor* editor : mEditors)
	{
		editor->Update();
	}
}

void GConsoleWindow::OnGUI()
{
	for (GEditor* editor : mEditors)
	{
		editor->OnGUI();
	}
}

void GConsoleWindow::Run()
{
	bool Active = (bool)GetState();
	ImGui::Begin(GetName().c_str(), &Active, GetFlag());

	Update();
	OnGUI();

	ImGui::End();
}

void GConsoleWindow::OnEnable()
{

}

void GConsoleWindow::OnDisable()
{

}

void GConsoleWindow::OnDestroy()
{

}
