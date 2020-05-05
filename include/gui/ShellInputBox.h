#pragma once

#include "InputBox.h"

#include <Shlwapi.h>

namespace libufm
{
    namespace GUI
    {
        class ShellInputBox : public InputBox
        {
        public:
            METHOD ShellInputBox(Window* parent);
        protected:
            METHOD void Show();
        };
    }
}
