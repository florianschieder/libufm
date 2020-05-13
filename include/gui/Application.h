#pragma once

#include <vector>

#include <Windows.h>
#include <CommCtrl.h>
#include <gdiplus.h>

#include "../libufmdef.h"

#include "../core/Environment.h"
#include "../core/Property.h"
#include "../../res/resource.h"

#include "../cppbul/cppbul_api.h"

using namespace libufm::Core;

namespace libufm
{
    namespace GUI
    {
        class Application final
        {
        public:
            METHOD Application(HINSTANCE h, int n, String name);

            METHOD int Exit();
            METHOD void Restart();

            METHOD void GetConfig(String key, int* value);
            METHOD String GetConfig(String key);
            METHOD void SetConfig(String key, int value);
            METHOD void SetConfig(String key, LPCWSTR value);

            METHOD String GetEnvironmentVar(String key);
            METHOD void SetEnvironmentVar(String key, String value);

            METHOD HIMAGELIST* GetShellImageBucketLarge();
            METHOD HIMAGELIST* GetShellImageBucketSmall();
            METHOD int GetInternalIconIndex(DWORD icon);
            METHOD HICON FetchFileIcon(String path);
            
            METHOD wchar_t* GetLanguageString(int id);

            METHOD void IndicateTimeIntensiveProcess();
            METHOD void UnindicateTimeIntensiveProcess();

        properties:
            Property<Application, Environment> AppEnvironment;
            Property<Application, HINSTANCE> AppInstance;
            Property<Application, HINSTANCE> LibInstance;
            Property<Application, int> ShowState;

        getters_setters:
            Getter Environment GetAppEnv(Application* app);
            Getter HINSTANCE GetAppInstance(Application* app);
            Getter HINSTANCE GetLibInstance(Application* app);
            Getter int GetShowState(Application* app);

        private:
            METHOD void InitializeApplicationComponents();
            METHOD void InitializeShellImageBucket();
            METHOD void InitializeCommonControls();
            METHOD void InitializeEnvironment();

            ULONG_PTR gdiplusToken;

            String m_appName;
            int m_iUpIconIndex;
            HIMAGELIST m_largeShellImageBucket;
            HIMAGELIST m_smallShellImageBucket;
            HCURSOR m_cursorHand;
            HCURSOR m_cursorWait;
            HICON m_iconUp;
            Environment m_Environment;
            HINSTANCE m_hAppInstance;
            HINSTANCE m_hLibraryInstance;
            int m_nCmdShow;
        };
    }
}
