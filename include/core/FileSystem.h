#include "../libufmdef.h"

namespace libufm
{
    namespace Core
    {
        namespace FileSystem
        {
            METHOD bool Copy(const wchar_t* source, const wchar_t* dest, bool overwrite);
            METHOD void EditFile(const wchar_t* file);
            METHOD bool FileExists(const wchar_t* file);
            METHOD bool IsDirectory(const wchar_t* path);
            METHOD bool IsFile(const wchar_t* path);
            METHOD bool Move(const wchar_t* source, const wchar_t* dest, bool overwrite);
            METHOD bool NewDirectory(const wchar_t* dir);
            METHOD void PrintFile(const wchar_t* file);
            METHOD bool RecycleFile(const wchar_t* file);
            METHOD bool RecycleFile(const wchar_t* file, HWND window);
            METHOD void RunElevated(const wchar_t* file);
            METHOD void ShowFileProperties(const wchar_t* file);
            METHOD void Start(const wchar_t* file);
            METHOD void Start(const wchar_t* file, const wchar_t* params);

            // internals
            void __internals_shell32_shellexecute(const wchar_t* file, const wchar_t* operation, const wchar_t* params);
        }
    }
}