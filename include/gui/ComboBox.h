#pragma once

#include "Control.h"
#include "../libufmdef.h"

namespace libufm
{
    namespace GUI
    {
        class ComboBox : public Control
        {
        public:
            METHOD ComboBox(Window* parent);

            METHOD void AddItem(String item);

            String SelectedItem;

            void (*OnSelectionChanged)(ComboBox* object, Window* parent) = nullptr;

        protected:
            METHOD void Show();

            METHOD static LRESULT CALLBACK MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
            METHOD LRESULT CALLBACK MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        };
    }
}