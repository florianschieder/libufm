#include <gui/ToolButton.h>

using namespace libufm::GUI;

METHOD ToolButton::ToolButton(ToolBar* toolBar)
    : Button(toolBar->Parent)
{
    this->toolBar = toolBar;
    this->Show();

    this->X = 0;
    this->Y = 0;
    this->Width = 24;
    this->Height = 24;
}

METHOD ToolButton::ToolButton(ToolBar* toolBar, int width, int height) : ToolButton(toolBar)
{
    this->X = 0;
    this->Y = 0;
    this->Width = width;
    this->Height = height;
}

METHOD void ToolButton::SetLocation(int num)
{
    this->SetPosition(
        15 + (num * 31),
        3);
}

METHOD void ToolButton::Show()
{
    Button::Show();
    toolBar->AddControl(this);
}
