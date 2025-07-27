#include "Windows/GProjectWindow.h"
#include "Editor/GEditor.h"



GProjectWindow::GProjectWindow()
{
	SetName("Project");
	SetSize(ImVec2(300, 600));
}

GProjectWindow::~GProjectWindow()
{

}

void GProjectWindow::Initialize()
{

}

void GProjectWindow::Update()
{
	for (GEditor* editor : mEditors)
	{
		editor->Update();
	}
}

void GProjectWindow::OnGUI()
{
	for (GEditor* editor : mEditors)
	{
		editor->OnGUI();
	}
}

void GProjectWindow::Run()
{
	bool Active = (bool)GetState();
	ImGui::Begin(GetName().c_str(), &Active, GetFlag());

	Update();
	OnGUI();

	ImGui::End();
}

void GProjectWindow::OnEnable()
{

}

void GProjectWindow::OnDisable()
{

}

void GProjectWindow::OnDestroy()
{

}
