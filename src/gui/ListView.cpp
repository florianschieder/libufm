#include <gui/ListView.h>

using namespace libufm::GUI;

METHOD ListView::ListView(Window* parent) : Control(parent)
{
    this->m_controlHandle = { 0 };
    this->Show();
}

void ListView::AddItem(int id, int imageID)
{
    LV_ITEM item = { 0 };
    item.mask = LVIF_IMAGE;
    item.iItem = id;
    item.iImage = imageID;

    ListView_InsertItem(
        this->m_controlHandle,
        &item);
}

void ListView::AddSubItem(int id, int subID, String Text)
{
    ListView_SetItemText(
        this->m_controlHandle,
        id,
        subID,
        (LPWSTR) Text.c_str());
}

METHOD void ListView::InitializeTimeIntensiveProcess()
{
    // Show wait cursor (global application function)
    ((Application*) this->m_parentWindow->AppContext)->IndicateTimeIntensiveProcess();

    // Force up insertion (deactivate redraw)
    SendMessage(this->m_controlHandle, WM_SETREDRAW, FALSE, 0);
}

METHOD void ListView::UninitializeTimeIntensiveProcess()
{
    // Re-activate redraw
    SendMessage(this->m_controlHandle, WM_SETREDRAW, TRUE, 0);

    // Show standard cursor (global application function)
    ((Application*) this->m_parentWindow->AppContext)->UnindicateTimeIntensiveProcess();
}

METHOD void ListView::Show()
{
    this->m_controlHandle = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        WC_LISTVIEW,
        L"",
        WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | this->specificStyles,
        0,
        0,
        0,
        0,
        this->m_parentWindow->Handle,
        (HMENU) this->m_ctrlID,
        ((Application*) this->m_parentWindow->AppContext)->AppInstance,
        NULL);

    SetWindowLongPtr(
        m_controlHandle,
        GWLP_USERDATA,
        (LONG_PTR)this);

    SetWindowSubclass(
        m_controlHandle,
        this->MessageLoopForwarder,
        0,
        0);

    SendMessage(
        this->m_controlHandle,
        LVM_SETEXTENDEDLISTVIEWSTYLE,
        0,
        LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

    SendMessage(
        this->m_controlHandle,
        WM_SETFONT,
        (WPARAM) this->defaultFont,
        TRUE);
}

METHOD void ListView::SetView(int view)
{
    SendMessage(
        this->m_controlHandle,
        LVM_SETVIEW,
        view,
        0);
}

METHOD void ListView::AddColumn(String Header, int width, int pos)
{
    LVCOLUMN lvc;

    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    lvc.iSubItem = 0;
    lvc.pszText = (LPWSTR) Header.c_str();
    lvc.cx = width;
    lvc.fmt = LVCFMT_LEFT;

    ListView_InsertColumn(
        this->m_controlHandle,
        pos,
        &lvc);
}

METHOD LRESULT ListView::MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    ListView* listView = (ListView*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    return listView->MessageLoop(hwnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
}

METHOD LRESULT ListView::MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}
