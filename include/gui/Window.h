#pragma once

#include "../libufmdef.h"

#include "../core/Property.h"

#include <memory>

#include "Application.h"

#define WM_POSTPARAM WM_USER + 1
#define WM_COMBOBOX_ITEM_CHANGED WM_USER + 2

namespace libufm
{
    namespace GUI
    {
        class Window;

        typedef struct _DialogBoxInformation
        {
            Window* window;
            LPCWSTR caption;
            LPCWSTR defaultValue;
        } DialogBoxInformation;

        class Window
        {
        public:
            METHOD Window(Application* app);
            METHOD Window(Application* app, Window* parent);

            METHOD void Close();
            METHOD void Destroy();
            METHOD void Show();
            METHOD int ShowMessage(String text, int style);
            METHOD int ShowMessage(String title, String text, int style);
            METHOD int ShowLastError(int style);
            METHOD static int ShowMessage(HINSTANCE hInstance, String title, String text, int style);
            METHOD void SpawnStandardDialog(int dlgId);
            METHOD void SpawnStandardInputDialog(const wchar_t* caption, int reason);
            METHOD void SpawnStandardInputDialog(const wchar_t* caption, int reason, const wchar_t* defaultInput);

            METHOD void FillRectangleWithBrush(HDC dc, int x, int y, int width, int height, COLORREF brush);
            METHOD void FillRectangleWithGradientH(HDC dc, int x, int y, int width, int height, COLORREF color1, COLORREF color2);
            METHOD void FillRectangleWithGradientV(HDC dc, int x, int y, int width, int height, COLORREF color1, COLORREF color2);

            int controlIDSequence = 50000;
            void* ActiveControl = nullptr;

            METHOD EventHandler CloseWindow(Window* window);
        
        properties:
            Property<Window, Application*> AppContext;
            Property<Window, int> ControlID;
            Property<Window, HFONT> Font;
            Property<Window, HWND> Handle;
            Property<Window, int> Height;
            Property<Window, HICON> Icon;
            Property<Window, bool> IsOpened;
            Property<Window, Window*> Parent;
            Property<Window, int> Style;
            Property<Window, String> Title;
            Property<Window, int> Width;
            Property<Window, int> X;
            Property<Window, int> Y;

        getters_setters:
            Getter Application* GetAppContext(Window* window);
            Setter SetAppContext(Window* window, Application* app);

            Getter int GetControlID(Window* window);
            Setter SetControlID(Window* window, int ctrlID);

            Getter HFONT GetFont(Window* window);
            Setter SetFont(Window* window, HFONT font);

            Getter HWND GetHandle(Window* window);

            Getter int GetHeight(Window* window);
            Setter SetHeight(Window* window, int height);

            Getter HICON GetIcon(Window* window);
            Setter SetIcon(Window* window, HICON icon);

            Getter bool GetIsOpened(Window* window);
            Setter SetIsOpened(Window* window, bool isOpened);

            Getter Window* GetParent(Window* window);
            Setter SetParent(Window* window, Window* parent);

            Getter int GetStyle(Window* window);
            Setter SetStyle(Window* window, int style);

            Getter String GetTitle(Window* window);
            Setter SetTitle(Window* window, String title);

            Getter int GetWidth(Window* window);
            Setter SetWidth(Window* window, int width);

            Getter int GetX(Window* window);
            Setter SetX(Window* window, int x);

            Getter int GetY(Window* window);
            Setter SetY(Window* window, int y);

        events:
            Event OnClose() = 0;
            Event OnInitializeWindow() = 0;
            Event OnKeyDown(DWORD key) = 0;
            Event OnMenuEvent(WORD id) = 0;
            Event OnPaint(PAINTSTRUCT ps, HDC hdc) = 0;
            Event OnPostParam(void* param, int reason) = 0;
            Event OnResizeWindow() = 0;

        internals:
            METHOD int Create();

        inheritables:
            int m_currentPostReason = 0;
            bool m_isOpen = false;

            int m_ctrlID = 50000;
            HFONT m_hFont = NULL;
            int m_style = 0;
            int m_iconID = 0;
            int m_menuID = 0;

            Application* m_application;
            HWND m_windowHandle;
            Window* m_parentWindow;
            WNDCLASS m_windowClass;

            METHOD static LRESULT CALLBACK MessageLoopForwarder(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
            METHOD LRESULT CALLBACK MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
            
            METHOD static INT_PTR CALLBACK StandardInputDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
            METHOD static INT_PTR CALLBACK StandardDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
        };
    }
}
