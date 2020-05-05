#pragma once

#include "Control.h"
#include "Window.h"

namespace libufm
{
    namespace GUI
    {
        class InputBox : public Control
        {
        public:
            METHOD InputBox(Window* parent);

            void* (*OnTextChanged)() = nullptr;

        protected:
            METHOD void Show();

            METHOD static LRESULT CALLBACK MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
            METHOD LRESULT CALLBACK MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        };
    }
}
