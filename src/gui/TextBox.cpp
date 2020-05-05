#include <gui/TextBox.h>

using namespace libufm::GUI;

using namespace libufm::Core::FileDetection;

METHOD TextBox::TextBox(Window* parent)
    : TextBox(parent, false)
{
}

METHOD TextBox::TextBox(Window* parent, bool bReadOnly) : Control(parent)
{
    this->bReadOnly = bReadOnly;

    this->hFont = CreateFont(
        PT(10),
        0,
        0,
        0,
        FW_DONTCARE,
        FALSE,
        FALSE,
        FALSE,
        ANSI_CHARSET,
        OUT_TT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_DONTCARE,
        TEXT("Courier New"));

    this->Show();
}

METHOD void TextBox::Show()
{
    int styles = ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL
        | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL;

    if (this->bReadOnly)
        styles = styles | ES_READONLY;

    this->m_controlHandle = CreateWindowEx(
        0,
        L"EDIT",
        L"",
        styles,
        0,
        0,
        0,
        0,
        this->m_parentWindow->Handle,
        (HMENU)0,
        ((Application*)this->m_parentWindow->AppContext)->AppInstance,
        NULL);

    SetWindowLongPtr(
        Handle,
        GWLP_USERDATA,
        (LONG_PTR)this);

    SetWindowSubclass(
        this->Handle,
        this->MessageLoopForwarder,
        0,
        0);

    SendMessage(
        this->Handle,
        WM_SETFONT,
        (WPARAM)this->hFont,
        TRUE);
}

METHOD TextBox::~TextBox()
{
    DeleteObject(this->hFont);
}

METHOD void TextBox::ReadBinaryFile(String file)
{
    char* fileContent;
    unsigned int fileSize = 0L;

    std::ifstream is(file, std::ifstream::binary);

    if (is)
    {
        is.seekg(0, is.end);
        fileSize = (unsigned int) is.tellg();
        is.seekg(0, is.beg);

        unsigned int offs = fileSize;
        offs += 1;

        fileContent = new char[offs];

        is.read(fileContent, fileSize);

        for (unsigned int i = 0; i < fileSize; i++)
        {
            if (fileContent[i] <= 0 || fileContent[i] == '\n' || fileContent[i] == '\r')
            {
                fileContent[i] = '.';
            }
        }

        fileContent[fileSize] = '\0';

        SendMessageA(
            this->Handle,
            WM_SETTEXT,
            0,
            (LPARAM)fileContent);

        delete[] fileContent;

        is.close();
    }
}

METHOD void TextBox::ReadTextFile(String file)
{
    long fileSize;
    FILE* fp;

    _wfopen_s(
        &fp,
        file.c_str(),
        L"rb");

    if (fp)
    {
        // Get file size

        fseek(fp, 0, SEEK_END);
        fileSize = ftell(fp);
        rewind(fp);

        long offs = fileSize + 1L;

        if (IsUnicode(fp))
        {
            // Read unicode file buffer

            wchar_t* fileContent = new wchar_t[offs];
            fread_s(fileContent, fileSize * sizeof(wchar_t), sizeof(wchar_t), fileSize, fp);
            fileContent[fileSize] = L'\0';

            SendMessageW(
                this->Handle,
                WM_SETTEXT,
                0,
                (LPARAM)fileContent);

            delete[] fileContent;
        }
        else
        {
            // Read ansi file buffer

            char* fileContent = new char[offs];
            fread_s(fileContent, fileSize, 1, fileSize, fp);
            fileContent[fileSize] = '\0';

            SendMessageA(
                this->Handle,
                WM_SETTEXT,
                0,
                (LPARAM)fileContent);

            delete[] fileContent;
        }

        fclose(fp);
    }
}

METHOD LRESULT TextBox::MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    TextBox* txt = (TextBox*)GetWindowLongPtr(
        hwnd,
        GWLP_USERDATA);

    return txt->MessageLoop(hwnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
}

METHOD LRESULT TextBox::MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
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
