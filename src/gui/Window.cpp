#include <gui/Window.h>

using namespace libufm::GUI;

METHOD Window::Window(Application* app)
{
    this->m_windowHandle = { 0 };
    this->m_parentWindow = { 0 };
    this->m_windowClass = { };

    this->m_iconID = -1;
    this->m_menuID = -1;

    this->AppContext = Property<Window, Application*>(
        this,
        &this->GetAppContext,
        &this->SetAppContext,
        app);

    this->ControlID = Property<Window, int>(
        this,
        &this->GetControlID,
        &this->SetControlID,
        50000);

    this->Font = Property<Window, HFONT>(
        this,
        &this->GetFont,
        &this->SetFont,
        NULL);

    this->Handle = Property<Window, HWND>(
        this,
        &this->GetHandle);

    this->Height = Property<Window, int>(
        this,
        &this->GetHeight,
        &this->SetHeight,
        0,
        false);

    this->Icon = Property<Window, HICON>(
        this,
        &this->GetIcon,
        &this->SetIcon,
        NULL);

    this->IsOpened = Property<Window, bool>(
        this,
        &this->GetIsOpened,
        &this->SetIsOpened,
        false);

    this->Parent = Property<Window, Window*>(
        this,
        &this->GetParent,
        &this->SetParent,
        nullptr);

    this->Style = Property<Window, int>(
        this,
        &this->GetStyle,
        &this->SetStyle,
        WS_OVERLAPPEDWINDOW);

    this->Title = Property<Window, String>(
        this,
        &this->GetTitle,
        &this->SetTitle,
        L"",
        false);

    this->Width = Property<Window, int>(
        this,
        &this->GetWidth,
        &this->SetWidth,
        0,
        false);

    this->X = Property<Window, int>(
        this,
        &this->GetX,
        &this->SetX,
        0,
        false);

    this->Y = Property<Window, int>(
        this,
        &this->GetY,
        &this->SetY,
        0,
        false);
}

METHOD Window::Window(Application* app, Window* parent) : Window(app)
{
    this->m_parentWindow = parent;
}

METHOD int Window::Create()
{
    MakeUniqueClassNameW(className, L"WINDOW");

    this->m_windowClass = { };

    this->m_windowClass.lpfnWndProc = this->MessageLoopForwarder;
    this->m_windowClass.hInstance = this->m_application->AppInstance;
    this->m_windowClass.lpszClassName = className.c_str();
    this->m_windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

    if(this->m_iconID != -1)
        this->m_windowClass.hIcon = LoadIcon(
            this->m_application->AppInstance,
            MAKEINTRESOURCE(this->m_iconID));

    if(this->m_menuID != -1)
        this->m_windowClass.lpszMenuName = MAKEINTRESOURCE(this->m_menuID);

    if (!RegisterClass(&this->m_windowClass)) return -1;

    this->m_windowHandle = CreateWindowEx(
        0,
        this->m_windowClass.lpszClassName,
        L"Window",
        this->m_style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        (this->Parent == NULL) ? NULL : ((Window*)this->Parent)->Handle,
        NULL,
        this->m_application->AppInstance,
        this);

    return (this->m_windowHandle == NULL) ? -2 : 0;
}

METHOD void Window::Show()
{
    if (this->Create() == 0)
    {
        this->m_isOpen = true;
        ShowWindow(this->m_windowHandle, SW_SHOW);

        if (this->m_parentWindow == NULL)
        {
            MSG msg = { };
            while (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
}

METHOD int Window::ShowMessage(String text, int style)
{
    return ShellMessageBox(
        ((Application*)this->AppContext)->AppInstance,
        this->Handle,
        text.c_str(),
        ((String)this->Title).c_str(),
        style);
}

METHOD int Window::ShowMessage(String title, String text, int style)
{
    return ShellMessageBox(
        ((Application*) this->AppContext)->AppInstance,
        this->Handle,
        text.c_str(),
        title.c_str(),
        style);
}

METHOD int Window::ShowMessage(HINSTANCE hInstance, String title, String text, int style)
{
    return ShellMessageBox(
        hInstance,
        NULL,
        text.c_str(),
        title.c_str(),
        style);
}

METHOD void libufm::GUI::Window::SpawnStandardDialog(int dlgId)
{
    DialogBox(
        ((Application*)this->AppContext)->AppInstance,
        MAKEINTRESOURCE(dlgId),
        this->Handle,
        &this->StandardDlgProc);
}

METHOD void libufm::GUI::Window::SpawnStandardInputDialog(const wchar_t* caption, int reason)
{
    SpawnStandardInputDialog(caption, reason, (const wchar_t*) L"");
}

METHOD void libufm::GUI::Window::SpawnStandardInputDialog(const wchar_t* caption, int reason, const wchar_t* defaultInput)
{
    this->m_currentPostReason = reason;

    DialogBoxInformation inf = { 0 };

    inf.caption = caption;
    inf.window = this;
    inf.defaultValue = defaultInput;

    DialogBoxParam(
        ((Application*)this->AppContext)->LibInstance,
        MAKEINTRESOURCE(IDD_INPUTBOX),
        this->Handle,
        &this->StandardInputDlgProc,
        (LPARAM) &inf);
}

METHOD int Window::ShowLastError(int style)
{
    LPTSTR errorText = NULL;

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&errorText,
        0,
        NULL);

    if (NULL != errorText)
    {
        int result = this->ShowMessage(errorText, style);

        LocalFree(errorText);
        errorText = NULL;

        return result;
    }

    return -1;
}

METHOD void Window::Destroy()
{
    DestroyWindow(this->m_windowHandle);
    this->m_isOpen = false;
}

METHOD void Window::Close()
{
    SendMessage(this->m_windowHandle, WM_CLOSE, 0, 0);
}

METHOD LRESULT CALLBACK Window::MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_NOTIFY:
            SendMessage(
                GetDlgItem(
                    hwnd,
                    (int) wParam),
                WM_NOTIFY,
                ((LPNMHDR)lParam)->code,
                lParam);
            break;

        case WM_KEYDOWN:
            this->OnKeyDown(
                (DWORD) wParam);
            break;

        case WM_COMMAND:
            switch (HIWORD(wParam))
            {
                case CBN_SELCHANGE:
                    SendMessage(
                        (HWND) lParam,
                        WM_COMBOBOX_ITEM_CHANGED,
                        0,
                        0);
                    break;

                case BN_CLICKED:
                    SendMessage(
                        GetDlgItem(hwnd, LOWORD(wParam)),
                        WM_COMMAND,
                        wParam,
                        lParam);

                    if (GetLastError() == ERROR_INVALID_WINDOW_HANDLE)
                    {
                        // It was a menu
                        this->OnMenuEvent(LOWORD(wParam));
                    }
                    break;

                case BN_DOUBLECLICKED:
                    SendMessage(
                        GetDlgItem(hwnd, LOWORD(wParam)),
                        WM_COMMAND,
                        wParam,
                        lParam);
                    break;
            }
            return 0;

        case WM_CLOSE:
            this->OnClose();
            return 0;

        case WM_DESTROY:
            UnregisterClass(
                this->m_windowClass.lpszClassName,
                this->m_application->AppInstance);
            
            if(this->m_parentWindow == nullptr) PostQuitMessage(0);

            return 0;

        case WM_POSTPARAM:
            this->OnPostParam(
                (void*) wParam,
                (int) lParam);
            return 0;

        case WM_CREATE:
            this->m_windowHandle = hwnd;

            this->OnInitializeWindow();

            return 0;

        case WM_SIZE:
            this->OnResizeWindow();

            return 0;

        case WM_PAINT:
        {
            this->m_windowHandle = hwnd;

            InvalidateRgn(this->m_windowHandle, NULL, TRUE);

            PAINTSTRUCT ps;
            RECT rect = { 0 };
            HDC paint_hdc;

            HBRUSH bgBrush = CreateSolidBrush(
                RGB(240, 240, 240));

            paint_hdc = BeginPaint(hwnd, &ps);
            rect.left = 0;
            rect.top = 0;
            rect.right = this->Width;
            rect.bottom = this->Height;
            ps.rcPaint = rect;

            FillRect(
                paint_hdc,
                &rect,
                bgBrush);

            this->OnPaint(ps, paint_hdc);

            EndPaint(hwnd, &ps);
            
            DeleteDC(paint_hdc);
            DeleteObject(bgBrush);

            return 0;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

METHOD INT_PTR libufm::GUI::Window::StandardInputDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        DialogBoxInformation* inf = (DialogBoxInformation*)lParam;
        SetWindowText(
            hDlg,
            (String(((Window*)inf->window)->Title).c_str()));

        SetDlgItemText(
            hDlg,
            IDC_INPUTBOX_CAPTION,
            inf->caption);

        SetDlgItemText(
            hDlg,
            IDC_INPUTBOX_INPUTFIELD, 
            inf->defaultValue);

        SetWindowLongPtr(
            hDlg,
            GWLP_USERDATA,
            (LONG_PTR) inf);

        return TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            wchar_t str[MAX_PATH];
            GetDlgItemText(hDlg, IDC_INPUTBOX_INPUTFIELD, str, MAX_PATH);

            HWND parent = ::GetParent(hDlg);

            DialogBoxInformation* inf = (DialogBoxInformation*)GetWindowLongPtr(
                hDlg, GWLP_USERDATA);

            Window* wnd = inf->window;
            
            if (parent != wnd->Handle)
            {
                throw std::exception("Something badly went wrong with passing parent window to dialog box");
            }

            SendMessage(
                parent,
                WM_POSTPARAM,
                (WPARAM)str,
                wnd->m_currentPostReason);

            EndDialog(hDlg, IDOK);

            break;
        }
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            break;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

METHOD INT_PTR libufm::GUI::Window::StandardDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hDlg, IDOK);
            break;
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            break;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

METHOD LRESULT CALLBACK Window::MessageLoopForwarder(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* wnd;
    if (msg == WM_CREATE)
    {
        wnd = (Window*)(((LPCREATESTRUCT)lParam)->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)wnd);
    }
    else
    {
        wnd = (Window*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    return wnd->MessageLoop(hWnd, msg, wParam, lParam);
}

METHOD void Window::CloseWindow(Window* window)
{
    window->Destroy();
}

Application* Window::GetAppContext(Window* window)
{
    return window->m_application;
}

void Window::SetAppContext(Window* window, Application* app)
{
    window->m_application = app;
}

int libufm::GUI::Window::GetControlID(Window* window)
{
    return window->m_ctrlID;
}

void libufm::GUI::Window::SetControlID(Window* window, int ctrlID)
{
    window->m_ctrlID = ctrlID;
}

HFONT libufm::GUI::Window::GetFont(Window* window)
{
    return window->m_hFont;
}

void libufm::GUI::Window::SetFont(Window* window, HFONT font)
{
    window->m_hFont = font;
}

HWND libufm::GUI::Window::GetHandle(Window* window)
{
    return window->m_windowHandle;
}

int libufm::GUI::Window::GetHeight(Window* window)
{
    RECT rect = { 0 };

    GetClientRect(window->Handle, &rect);

    return (rect.bottom - rect.top);
}

void libufm::GUI::Window::SetHeight(Window* window, int height)
{
    SetWindowPos(
        window->Handle,
        0,
        window->X, window->Y,
        window->Width, height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}

HICON libufm::GUI::Window::GetIcon(Window* window)
{
    return (HICON) SendMessage(
        window->Handle, WM_GETICON, ICON_SMALL, 0);
}

void libufm::GUI::Window::SetIcon(Window* window, HICON icon)
{
    SendMessage(
        window->Handle, WM_SETICON, ICON_SMALL, (LPARAM) icon);

    SendMessage(
        window->Handle, WM_SETICON, ICON_BIG, (LPARAM) icon);
}

bool libufm::GUI::Window::GetIsOpened(Window* window)
{
    return window->m_isOpen;
}

void libufm::GUI::Window::SetIsOpened(Window* window, bool isOpened)
{
    window->m_isOpen = isOpened;
}

Window* libufm::GUI::Window::GetParent(Window* window)
{
    return window->m_parentWindow;
}

void libufm::GUI::Window::SetParent(Window* window, Window* parent)
{
    window->m_parentWindow = parent;
}

int libufm::GUI::Window::GetStyle(Window* window)
{
    return window->m_style;
}

void libufm::GUI::Window::SetStyle(Window* window, int style)
{
    window->m_style = style;
}

String Window::GetTitle(Window* window)
{
    wchar_t title[300];
    GetWindowText(window->m_windowHandle, title, 300);
    return title;
}

void Window::SetTitle(Window* window, String Title)
{
    SendMessage(
        window->m_windowHandle,
        WM_SETTEXT,
        0,
        (LPARAM)Title.c_str());
}

int libufm::GUI::Window::GetWidth(Window* window)
{
    RECT rect = { 0 };

    GetClientRect(window->Handle, &rect);

    return (rect.right - rect.left);
}

void libufm::GUI::Window::SetWidth(Window* window, int width)
{
    SetWindowPos(
        window->Handle,
        0,
        window->X, window->Y,
        width, window->Height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}

int libufm::GUI::Window::GetX(Window* window)
{
    RECT rect = { 0 };

    GetWindowRect(window->Handle, &rect);

    return rect.left;
}

void libufm::GUI::Window::SetX(Window* window, int x)
{
    SetWindowPos(
        window->Handle,
        0,
        x, window->Y,
        window->Width, window->Height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}

int libufm::GUI::Window::GetY(Window* window)
{
    RECT rect = { 0 };

    GetWindowRect(window->Handle, &rect);

    return rect.top;
}

void libufm::GUI::Window::SetY(Window* window, int y)
{
    SetWindowPos(
        window->Handle,
        0,
        window->X, y,
        window->Width, window->Height,
        SWP_NOZORDER | SWP_SHOWWINDOW);
}


METHOD void Window::FillRectangleWithBrush(HDC dc, int x, int y, int width, int height, COLORREF brush)
{
    Gdiplus::Graphics graphics(dc);

    Gdiplus::RectF rect(
        (Gdiplus::REAL) x,
        (Gdiplus::REAL) y,
        (Gdiplus::REAL) width,
        (Gdiplus::REAL) height);

    Gdiplus::SolidBrush background(Gdiplus::Color(
        GetRValue(brush),
        GetGValue(brush),
        GetBValue(brush)));

    graphics.FillRectangle(&background, rect);
}

METHOD void Window::FillRectangleWithGradientH(HDC dc, int x, int y, int width, int height, COLORREF color1, COLORREF color2)
{
    Gdiplus::Graphics graphics(dc);

    Gdiplus::RectF rect(
        (Gdiplus::REAL) x,
        (Gdiplus::REAL) y,
        (Gdiplus::REAL) width,
        (Gdiplus::REAL) height);

    Gdiplus::Color c1(Gdiplus::Color(
        GetRValue(color1),
        GetGValue(color1),
        GetBValue(color1)));

    Gdiplus::Color c2(Gdiplus::Color(
        GetRValue(color2),
        GetGValue(color2),
        GetBValue(color2)));

    Gdiplus::LinearGradientBrush background(
        rect,
        c1,
        c2,
        Gdiplus::LinearGradientMode::LinearGradientModeHorizontal);

    graphics.FillRectangle(&background, rect);
}

METHOD void Window::FillRectangleWithGradientV(HDC dc, int x, int y, int width, int height, COLORREF color1, COLORREF color2)
{
    Gdiplus::Graphics graphics(dc);

    Gdiplus::RectF rect(
        (Gdiplus::REAL) x,
        (Gdiplus::REAL) y,
        (Gdiplus::REAL) width,
        (Gdiplus::REAL) height);

    Gdiplus::Color c1(Gdiplus::Color(
        GetRValue(color1),
        GetGValue(color1),
        GetBValue(color1)));

    Gdiplus::Color c2(Gdiplus::Color(
        GetRValue(color2),
        GetGValue(color2),
        GetBValue(color2)));

    Gdiplus::LinearGradientBrush background(
        rect,
        c1,
        c2,
        Gdiplus::LinearGradientMode::LinearGradientModeVertical);

    graphics.FillRectangle(&background, rect);
}
