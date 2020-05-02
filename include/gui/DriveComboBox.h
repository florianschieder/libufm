#pragma once

#include "ComboBox.h"

namespace libufm
{
    namespace GUI
    {
        class DriveComboBox
            : public ComboBox
        {
        public:
            METHOD DriveComboBox(Window* parent);
            METHOD void Show();
        };
    }
}
