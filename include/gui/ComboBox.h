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

            void (*OnSelectionChanged)(ComboBox* object, Window* parent) = nullptr;

        properties:
            Property<ComboBox, String> SelectedItem;

        getters_setters:
            Getter String GetSelectedItem(ComboBox* object);
            Setter SetSelectedItem(ComboBox* object, String item);

        protected:
            METHOD void Show();

            METHOD static LRESULT CALLBACK MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
            METHOD LRESULT CALLBACK MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

            String m_SelectedItem;
        };
    }
}