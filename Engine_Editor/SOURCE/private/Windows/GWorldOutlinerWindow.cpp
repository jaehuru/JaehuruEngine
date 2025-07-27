#include "Windows/GWorldOutlinerWindow.h"
#include "Editor/GEditor.h"



GWorldOutlinerWindow::GWorldOutlinerWindow()
{
	SetName("World Outliner");
	SetSize(ImVec2(300, 600));
}

GWorldOutlinerWindow::~GWorldOutlinerWindow()
{

}

void GWorldOutlinerWindow::Initialize()
{

}

void GWorldOutlinerWindow::Update()
{
	for (GEditor* editor : mEditors)
	{
		editor->Update();
	}
}

void GWorldOutlinerWindow::OnGUI()
{
	for (GEditor* editor : mEditors)
	{
		editor->OnGUI();
	}
}

void GWorldOutlinerWindow::Run()
{
	bool Active = (bool)GetState();
	ImGui::Begin(GetName().c_str(), &Active, GetFlag());

	Update();
	OnGUI();

	ImGui::End();
}

void GWorldOutlinerWindow::OnEnable()
{

}

void GWorldOutlinerWindow::OnDisable()
{

}

void GWorldOutlinerWindow::OnDestroy()
{

}
