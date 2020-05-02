#include <gui/Image.h>

using namespace libufm::GUI;

METHOD Image::Image(Window* parent, String path) : Control(parent)
{
    this->path = path;

    this->img = new Gdiplus::Image(path.c_str());
    
    this->realDX = img->GetWidth();
    this->realDY = img->GetHeight();

    this->Show();
}

METHOD Image::~Image()
{
    delete this->img;
}

METHOD void Image::Show()
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
        (HMENU)-2,
        ((Application*) this->m_parentWindow->AppContext)->AppInstance,
        this);

    SetWindowLongPtr(
        this->m_controlHandle,
        GWLP_USERDATA,
        (LONG_PTR)this);

    SetWindowSubclass(
        this->m_controlHandle,
        &this->MessageLoopForwarder,
        0,
        0);
}

METHOD int Image::GetRealWidth()
{
    return this->realDX;
}

METHOD int Image::GetRealHeight()
{
    return this->realDY;
}

METHOD bool Image::CanResize()
{
    return canResize;
}

METHOD LRESULT Image::MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    Image* img = (Image*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    return img->MessageLoop(hwnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
}

METHOD LRESULT Image::MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
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

METHOD void Image::OnDraw(HDC hdc)
{
    Gdiplus::Graphics graphics(hdc);
    
    if (this->Width < 400 && this->Height < 300)
    {
        graphics.DrawImage(
            this->img, 0, 0, this->img->GetWidth(), this->img->GetHeight());
        canResize = false;
    }
    else
    {
        graphics.DrawImage(this->img, 0, 0, this->Width, this->Height);
    }
}
