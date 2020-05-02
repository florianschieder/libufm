#include <gui/DriveComboBox.h>

using namespace libufm::GUI;

METHOD DriveComboBox::DriveComboBox(Window* parent) : ComboBox(parent)
{
    this->Show();
}

METHOD void DriveComboBox::Show()
{
    ComboBox::Show();

    DWORD dwSize = MAX_PATH;
    TCHAR szLogicalDrives[MAX_PATH] = { 0 };
    DWORD dwResult = GetLogicalDriveStrings(dwSize, szLogicalDrives);

    if (dwResult > 0 && dwResult <= MAX_PATH)
    {
        TCHAR* szSingleDrive = szLogicalDrives;
        while (*szSingleDrive)
        {
            this->AddItem(szSingleDrive);
            szSingleDrive += lstrlen(szSingleDrive) + sizeof(CHAR);
        }
    }

    /*SendMessage(
        this->m_controlHandle,
        CB_SETCURSEL,
        0,
        0);*/
}
