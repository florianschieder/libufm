#include <gui/Control.h>

using namespace libufm::GUI;

METHOD Control::Control(Window* parent)
{
    this->ControlID = Property<Control, long long>(
        this,
        &this->GetControlID,
        &this->SetControlID,
        0);

    this->Font = Property<Control, HFONT>(
        this,
        &this->GetFont,
        &this->SetFont,
        NULL);

    this->Handle = Property<Control, HWND>(
        this,
        &this->GetHandle);

    this->Height = Property<Control, int>(
        this,
        &this->GetHeight,
        &this->SetHeight,
        0,
        false);

    this->Icon = Property<Control, HICON>(
        this,
        &this->GetIcon,
        &this->SetIcon,
        NULL);

    this->Parent = Property<Control, Window*>(
        this,
        &this->GetParent,
        &this->SetParent,
        parent);

    this->Style = Property<Control, int>(
        this,
        &this->GetStyle,
        &this->SetStyle,
        WS_OVERLAPPEDWINDOW);

    this->Text = Property<Control, String>(
        this,
        &this->GetText,
        &this->SetText,
        L"",
        false);

    this->Width = Property<Control, int>(
        this,
        &this->GetWidth,
        &this->SetWidth,
        0,
        false);

    this->X = Property<Control, int>(
        this,
        &this->GetX,
        &this->SetX,
        0,
        false);

    this->Y = Property<Control, int>(
        this,
        &this->GetY,
        &this->SetY,
        0,
        false);

    this->defaultFont = CreateFont(
        PT(9),
        0,
        0,
        0,
        FW_REGULAR,
        FALSE,
        FALSE,
        FALSE,
        ANSI_CHARSET,
        OUT_TT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        TEXT("Tahoma"));

    this->m_className = L"";
    this->m_controlHandle = { 0 };
    this->m_ctrlID = 0;

    this->ControlID = parent->controlIDSequence;
    parent->controlIDSequence++;
}

METHOD Control::~Control()
{
    DeleteObject(this->defaultFont);
}

METHOD void Control::AddToolTip(const TCHAR text[80])
{
    HWND hwndTip = CreateWindowEx(
        NULL,
        TOOLTIPS_CLASS,
        NULL,
        WS_POPUP | TTS_ALWAYSTIP,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        this->m_parentWindow->Handle,
        NULL,
        ((Application*) this->m_parentWindow->AppContext)->AppInstance,
        NULL);

    if (!this->m_controlHandle || !hwndTip)
    {
        return;
    }

    // Associate the tooltip with the tool.
    TOOLINFO toolInfo = { 0 };
    toolInfo.cbSize = sizeof(toolInfo);
    toolInfo.hwnd = this->m_parentWindow->Handle;
    toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    toolInfo.uId = (UINT_PTR) this->m_controlHandle;
    toolInfo.lpszText = (LPWSTR) text;
    
    SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);
}

METHOD void libufm::GUI::Control::SetPosition(int x, int y)
{
    this->Place(x, y, this->Width, this->Height);
}

METHOD void libufm::GUI::Control::SetSize(int width, int height)
{
    this->Place(this->X, this->Y, width, height);
}

METHOD void libufm::GUI::Control::Place(int x, int y, int width, int height)
{
    SetWindowPos(
        this->Handle,
        0,
        x, y, width, height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}

long long Control::GetControlID(Control* control)
{
    return control->m_ctrlID;
}

void Control::SetControlID(Control* control, long long ctrlID)
{
    control->m_ctrlID = ctrlID;
}

HFONT Control::GetFont(Control* control)
{
    return control->defaultFont;
}

void Control::SetFont(Control* control, HFONT font)
{
    control->defaultFont = font;
}

HWND Control::GetHandle(Control* control)
{
    return control->m_controlHandle;
}

int Control::GetHeight(Control* control)
{
    RECT rect = { 0 };

    GetWindowRect(control->Handle, &rect);

    return (rect.bottom - rect.top);
}

void Control::SetHeight(Control* control, int height)
{
    SetWindowPos(
        control->Handle,
        0,
        control->X, control->Y,
        control->Width, height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}

HICON Control::GetIcon(Control* control)
{
    return (HICON)SendMessage(
        control->Handle, WM_GETICON, ICON_SMALL, 0);
}

void Control::SetIcon(Control* control, HICON icon)
{
    SendMessage(
        control->Handle, WM_SETICON, ICON_SMALL, (LPARAM)icon);

    SendMessage(
        control->Handle, WM_SETICON, ICON_BIG, (LPARAM)icon);
}

Window* Control::GetParent(Control* control)
{
    return control->m_parentWindow;
}

void Control::SetParent(Control* control, Window* parent)
{
    control->m_parentWindow = parent;
}

int Control::GetStyle(Control* control)
{
    return control->specificStyles;
}

void Control::SetStyle(Control* control, int style)
{
    control->specificStyles = style;
}

String Control::GetText(Control* control)
{
    wchar_t text[300];
    GetWindowText(control->Handle, text, 300);
    return text;
}

void Control::SetText(Control* control, String Title)
{
    SendMessage(
        control->Handle,
        WM_SETTEXT,
        0,
        (LPARAM)Title.c_str());
}

int Control::GetWidth(Control* window)
{
    RECT rect = { 0 };

    GetWindowRect(window->Handle, &rect);

    return (rect.right - rect.left);
}

void Control::SetWidth(Control* window, int width)
{
    SetWindowPos(
        window->Handle,
        0,
        window->X, window->Y,
        width, window->Height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}

int Control::GetX(Control* window)
{
    RECT rect = { 0 };
    GetWindowRect(window->Handle, &rect);

    POINT pt = { rect.left, rect.top };
    ScreenToClient(
        ((Window*)window->Parent)->Handle, &pt);

    return pt.x;
}

void Control::SetX(Control* window, int x)
{
    SetWindowPos(
        window->Handle,
        0,
        x, window->Y,
        window->Width, window->Height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}

int Control::GetY(Control* window)
{
    RECT rect = { 0 };
    GetWindowRect(window->Handle, &rect);

    POINT pt = { rect.left, rect.top };
    ScreenToClient(
        ((Window*) window->Parent)->Handle, &pt);

    return pt.y;
}

void Control::SetY(Control* window, int y)
{
    SetWindowPos(
        window->Handle,
        0,
        window->X, y,
        window->Width, window->Height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}
