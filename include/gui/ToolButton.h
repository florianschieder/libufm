#pragma once

#include "Button.h"
#include "ToolBar.h"

namespace libufm
{
    namespace GUI
    {
        class ToolButton : public Button
        {
        public:
            METHOD ToolButton(ToolBar* toolBar);
            METHOD ToolButton(ToolBar* toolBar, int width, int height);
            METHOD void SetLocation(int num);
            METHOD void Show();

        private:
            ToolBar* toolBar;
        };
    }
}
