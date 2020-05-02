#include <gui/ShellInputBox.h>

using namespace libufm::GUI;

METHOD ShellInputBox::ShellInputBox(Window* parent, int x, int y, int width, int height) : InputBox(parent, x, y, width, height)
{
}

METHOD void ShellInputBox::Show()
{
    InputBox::Show();

    SHAutoComplete(
        this->m_controlHandle,
        SHACF_FILESYS_DIRS | SHACF_AUTOSUGGEST_FORCE_ON);

    SetWindowTheme(
        this->m_controlHandle,
        L"Explorer",
        NULL);
}
