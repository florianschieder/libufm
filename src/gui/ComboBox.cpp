#include <gui/ComboBox.h>

using namespace libufm::GUI;

METHOD ComboBox::ComboBox(Window* parent) : Control(parent)
{
    this->SelectedItem = Property<ComboBox, String>(
        this,
        &this->GetSelectedItem,
        &this->SetSelectedItem,
        L"",
        false);

    this->Show();
}

METHOD void ComboBox::AddItem(String item)
{
    SendMessage(
        this->m_controlHandle,
        CB_ADDSTRING,
        0,
        (LPARAM) item.c_str());
}

String ComboBox::GetSelectedItem(ComboBox* object)
{
    return object->m_SelectedItem;
}

void ComboBox::SetSelectedItem(ComboBox* object, String item)
{
    SendMessage(
        object->Handle,
        CB_SELECTSTRING,
        -1,
        (LPARAM) item.c_str());
}

METHOD void ComboBox::Show()
{
    this->m_controlHandle = CreateWindowEx(
        0,
        WC_COMBOBOX,
        L"",
        WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
        0,
        0,
        0,
        0,
        this->m_parentWindow->Handle,
        (HMENU) this->m_ctrlID,
        ((Application*)this->m_parentWindow->AppContext)->AppInstance,
        this);

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
        WM_SETFONT,
        (WPARAM) this->defaultFont,
        TRUE);
}

METHOD LRESULT ComboBox::MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    ComboBox* box = (ComboBox*) GetWindowLongPtr(hwnd, GWLP_USERDATA);
    return box->MessageLoop(hwnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
}

METHOD LRESULT ComboBox::MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
        case WM_COMBOBOX_ITEM_CHANGED:
        {
            TCHAR buffer[512];
            int idx;
            idx = (int)SendMessage(this->m_controlHandle, CB_GETCURSEL, 0, 0);
            SendMessage(this->m_controlHandle, CB_GETLBTEXT, idx, (LPARAM)buffer);

            buffer[511] = L'\0';

            this->m_SelectedItem = buffer;

            if (this->OnSelectionChanged != nullptr)
            {
                this->OnSelectionChanged(this, this->m_parentWindow);
            }
            break;
        }
        default:
            break;
    }

    return DefSubclassProc(hwnd, uMsg, wParam, lParam);
}
