#include <gui/ToolBar.h>

using namespace libufm::GUI;

METHOD ToolBar::ToolBar(Window* parent) : Control(parent)
{
    this->drawStartGripperX = -1;

    this->blackBrush = 0;
    this->whiteBrush = 0;
    this->toolbarSepBrush = 0;
    this->sepBrush = 0;

    this->Show();
}

METHOD ToolBar::~ToolBar()
{
}

void ToolBar::AddControl(Control* control)
{
    ::SetParent(
        control->Handle, this->Handle);
}

void ToolBar::Show()
{
    this->m_controlHandle = CreateWindowEx(
        0,
        TOOLBARCLASSNAME,
        L"",
        WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        ((Window*) this->Parent)->Handle,
        (HMENU) -1,
        ((Application*)this->m_parentWindow->AppContext)->AppInstance,
        this);

    SetWindowLongPtr(
        this->m_controlHandle,
        GWLP_USERDATA,
        (LONG_PTR) this);

    SetWindowSubclass(
        this->m_controlHandle,
        this->MessageLoopForwarder,
        0,
        0);
}

METHOD void ToolBar::AddStartGripper(int dx)
{
    this->drawStartGripperX = dx;
}

METHOD void ToolBar::AddSeparator(int x)
{
    this->separators.push_back(x);
}

METHOD void ToolBar::DrawStartGripper(HDC hdc, int dx)
{
    for (int i = 5; i <= this->Height - 7; i += 4)
    {
        RECT rect;
        
        rect.left = 5 + dx;
        rect.right = rect.left + 3;
        rect.top = i;
        rect.bottom = rect.top + 3;
        FillRect(hdc, &rect, this->whiteBrush);

        rect.left = 5 + dx;
        rect.right = rect.left + 2;
        rect.top = i;
        rect.bottom = rect.top + 2;
        FillRect(hdc, &rect, this->blackBrush);
    }
}

METHOD void ToolBar::DrawSeparator(HDC hdc, int x)
{
    RECT rect;

    rect = { x, 2, x + 1, this->Height - 5 };
    FillRect(hdc, &rect, this->sepBrush);
    rect = { x + 1, 2, x + 2, this->Height - 4 };
    FillRect(hdc, &rect, this->whiteBrush);
}

void ToolBar::OnDraw(HDC hdc)
{
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::RectF rectF(
        (Gdiplus::REAL) 0,
        (Gdiplus::REAL) 0,
        (Gdiplus::REAL) this->Width,
        (Gdiplus::REAL) this->Height);

    Gdiplus::LinearGradientBrush brush(
        rectF,
        Gdiplus::Color(240, 240, 240),
        Gdiplus::Color(208, 208, 208),
        Gdiplus::LinearGradientMode::LinearGradientModeVertical);

    graphics.FillRectangle(&brush, rectF);

    RECT rect;

    rect.left = 0;
    rect.right = this->Width;
    rect.top = this->Height - 2;
    rect.bottom = this->Height - 1;
    FillRect(hdc, &rect, this->toolbarSepBrush);
    
    rect.left = 0;
    rect.right = this->Width;
    rect.top = this->Height - 1;
    rect.bottom = this->Height;
    FillRect(hdc, &rect, this->whiteBrush);

    if(this->drawStartGripperX != -1) 
        this->DrawStartGripper(hdc, this->drawStartGripperX);
    
    for (unsigned int i = 0; i < this->separators.size(); i++)
    {
        this->DrawSeparator(hdc, this->separators[i]);
    }
}

METHOD LRESULT ToolBar::MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    ToolBar* toolbar = (ToolBar*) GetWindowLongPtr(hwnd, GWLP_USERDATA);

    return toolbar->MessageLoop(
        hwnd,
        uMsg,
        wParam,
        lParam,
        uIdSubclass,
        dwRefData);
}

METHOD LRESULT ToolBar::MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
        case WM_COMMAND:
            switch (HIWORD(wParam))
            {
                case BN_CLICKED:
                    SendMessage(
                        GetDlgItem(hwnd, LOWORD(wParam)),
                        WM_COMMAND,
                        wParam,
                        lParam);
                    break;
            }
            break;

        case WM_PAINT:
            PAINTSTRUCT ps;
            HDC hdc;

            InvalidateRgn(this->m_controlHandle, NULL, TRUE);

            this->toolbarSepBrush = CreateSolidBrush(
                RGB(182, 188, 204));
            this->blackBrush = CreateSolidBrush(
                RGB(0, 0, 0));
            this->whiteBrush = CreateSolidBrush(
                RGB(255, 255, 255));
            this->sepBrush = CreateSolidBrush(
                RGB(150, 150, 150));

            hdc = BeginPaint(hwnd, &ps);

            this->OnDraw(hdc);

            EndPaint(hwnd, &ps);

            DeleteObject(this->blackBrush);
            DeleteObject(this->whiteBrush);
            DeleteObject(this->toolbarSepBrush);
            DeleteObject(this->sepBrush);

            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
