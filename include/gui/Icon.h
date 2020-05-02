#pragma once

#include "Control.h"

namespace libufm
{
    namespace GUI
    {
        class Icon : public Control
        {
        public:
            METHOD Icon(Window* parent, int id);
            METHOD Icon(Window* parent, HICON hIcon);

        protected:
            METHOD void Show();

            METHOD static LRESULT CALLBACK MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
            METHOD LRESULT CALLBACK MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

            METHOD void OnDraw(HDC hdc);

            int iconID;
            HICON icon;
        };
    }
}
