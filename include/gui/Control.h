#pragma once

#include "Window.h"

namespace libufm
{
    namespace GUI
    {
        class Control {
        public:
            METHOD Control(Window* parent);
            METHOD ~Control();

            METHOD void AddToolTip(const TCHAR text[80]);
            METHOD void SetPosition(int x, int y);
            METHOD void SetSize(int width, int height);
            METHOD void Place(int x, int y, int width, int height);

        properties:
            Property<Control, long long> ControlID;
            Property<Control, HFONT> Font;
            Property<Control, HWND> Handle;
            Property<Control, int> Height;
            Property<Control, HICON> Icon;
            Property<Control, bool> IsOpened;
            Property<Control, Window*> Parent;
            Property<Control, int> Style;
            Property<Control, String> Text;
            Property<Control, int> Width;
            Property<Control, int> X;
            Property<Control, int> Y;

        getters_setters:
            Getter long long GetControlID(Control* window);
            Setter SetControlID(Control* window, long long ctrlID);

            Getter HFONT GetFont(Control* window);
            Setter SetFont(Control* window, HFONT font);

            Getter HWND GetHandle(Control* window);

            Getter int GetHeight(Control* window);
            Setter SetHeight(Control* window, int height);

            Getter HICON GetIcon(Control* window);
            Setter SetIcon(Control* window, HICON icon);

            Getter Window* GetParent(Control* window);
            Setter SetParent(Control* window, Window* parent);

            Getter int GetStyle(Control* window);
            Setter SetStyle(Control* window, int style);

            Getter String GetText(Control* window);
            Setter SetText(Control* window, String title);

            Getter int GetWidth(Control* window);
            Setter SetWidth(Control* window, int width);

            Getter int GetX(Control* window);
            Setter SetX(Control* window, int x);

            Getter int GetY(Control* window);
            Setter SetY(Control* window, int y);

        protected:
            HFONT defaultFont;

            int specificStyles = 0;

            long long m_ctrlID;

            String m_className;

            HWND m_controlHandle;
            Window* m_parentWindow;

            METHOD virtual void Show() = 0;
        };
    }
}
