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
        protected:
            METHOD void Show();
        };
    }
}
