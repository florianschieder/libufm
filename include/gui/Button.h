#pragma once

#include <Windows.h>

#include "../libufmdef.h"

#include "Control.h"
#include "Window.h"

namespace libufm
{
    namespace GUI
    {
        class Button : public Control
        {
        public:
            METHOD Button(Window* parent);
            METHOD ~Button();

            METHOD void SetIcon(int iconID, int w, int h);

            void (*OnClick)(Window* parent) = nullptr;

        protected:
            METHOD static LRESULT CALLBACK MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
            METHOD LRESULT CALLBACK MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

            METHOD void Show();

            int iconID;
            int iconWidth;
            int iconHeight;
            HICON iconHandle;
        };
    }
}
