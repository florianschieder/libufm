#include <gui/InputBox.h>

using namespace libufm::GUI;

METHOD InputBox::InputBox(Window* parent) : Control(parent)
{
    this->m_controlHandle = { 0 };
    this->Show();
}

METHOD void InputBox::Show()
{
    this->m_controlHandle = CreateWindowEx(
        0,
        L"EDIT",
        L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        0,
        0,
        0,
        0,
        this->m_parentWindow->Handle,
        (HMENU)0,
        ((Application*) this->m_parentWindow->AppContext)->AppInstance,
        NULL);

    SetWindowLongPtr(
        m_controlHandle,
        GWLP_USERDATA,
        (LONG_PTR)this);

    SetWindowSubclass(
        this->m_controlHandle,
        this->MessageLoopForwarder,
        0,
        0);

    SendMessage(
        this->m_controlHandle,
        WM_SETFONT,
        (WPARAM)this->defaultFont,
        TRUE);
}

METHOD LRESULT InputBox::MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    InputBox* input = (InputBox*) GetWindowLongPtr(
        hwnd,
        GWLP_USERDATA);

    return input->MessageLoop(hwnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
}

METHOD LRESULT InputBox::MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
        case WM_CHAR:
            if (this->OnTextChanged != nullptr)
                this->OnTextChanged();
            break;
    }

    return DefSubclassProc(
        hwnd,
        uMsg,
        wParam,
        lParam);
}
