#include <gui/Icon.h>

using namespace libufm::GUI;

METHOD Icon::Icon(Window* parent, int id) : Control(parent)
{
    this->iconID = id;
    this->icon = LoadIcon(
        ((Application*) this->m_parentWindow->AppContext)->AppInstance,
        MAKEINTRESOURCE(id));
    
    this->Show();
}

METHOD Icon::Icon(Window* parent, HICON hIcon) : Control(parent)
{
    this->iconID = -1;
    this->icon = hIcon;

    this->Show();
}

METHOD void Icon::Show()
{
    this->m_controlHandle = CreateWindowEx(
        0,
        L"STATIC",
        L"",
        WS_CHILD | WS_VISIBLE,
        0,
        0,
        0,
        0,
        this->m_parentWindow->Handle,
        (HMENU)-1,
        ((Application*) this->m_parentWindow->AppContext)->AppInstance,
        this);

    SetWindowLongPtr(
        this->m_controlHandle,
        GWLP_USERDATA,
        (LONG_PTR)this);

    SetWindowSubclass(
        this->m_controlHandle,
        this->MessageLoopForwarder,
        0,
        0);
}

METHOD LRESULT Icon::MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    Icon* toolbar = (Icon*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    return toolbar->MessageLoop(hwnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
}

METHOD LRESULT Icon::MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc;

            hdc = BeginPaint(hwnd, &ps);

            this->OnDraw(hdc);

            EndPaint(hwnd, &ps);

            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

METHOD void Icon::OnDraw(HDC hdc)
{
    DrawIcon(hdc, 0, 0, this->icon);
}
