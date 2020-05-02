#pragma once

#include "Control.h"

namespace libufm
{
    namespace GUI
    {
        class StatusBar : public Control
        {
        public:
            METHOD StatusBar(Window* parent);
            METHOD ~StatusBar();

            METHOD void AddControl(std::shared_ptr<Control> control);

            METHOD void AddStartGripper(int dx = 0);

            METHOD void OnDraw(HDC hdc);

            bool m_DrawResize = true;

        protected:
            METHOD void Show();

            METHOD static LRESULT CALLBACK MessageLoopForwarder(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
            METHOD LRESULT CALLBACK MessageLoop(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

            METHOD void DrawStartGripper(HDC hdc, int dx);

            int drawStartGripperX;

            HBRUSH whiteBrush;
            HBRUSH blackBrush;
            HBRUSH sepBrush;
        };
    }
}
