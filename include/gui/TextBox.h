#pragma once

#include <fstream>

#include <core/FileDetection.h>
#include <gui/InputBox.h>

namespace libufm
{
    namespace GUI
    {
        class TextBox : public InputBox
        {
        public:
            METHOD TextBox(Window* parent);
            METHOD ~TextBox();
            METHOD void Show();
            METHOD void ReadBinaryFile(String file);
            METHOD void ReadTextFile(String file);
        private:
            HFONT hFont;
        };
    }
}
