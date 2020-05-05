#pragma once

#include <fstream>

#include <core/FileDetection.h>
#include <gui/InputBox.h>

namespace libufm
{
    namespace GUI
    {
        class TextBox : public Control
        {
        public:
            METHOD TextBox(Window* parent);
            METHOD TextBox(Window* parent, bool bReadOnly);
            METHOD ~TextBox();
            METHOD void ReadBinaryFile(String file);
            METHOD void ReadTextFile(String file);

            void* (*OnTextChanged)() = nullptr;
        
        protected:
            METHOD void Show();

            bool bReadOnly;
            HFONT hFont;

            METHOD static LRESULT CALLBACK MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
            METHOD LRESULT CALLBACK MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        };
    }
}
