#include <core/FileSystem.h>
#include <Shlwapi.h>

METHOD bool libufm::Core::FileSystem::Copy(const wchar_t* source, const wchar_t* dest, bool overwrite)
{
    return CopyFile(
        source, dest, !overwrite);
}

METHOD void libufm::Core::FileSystem::EditFile(const wchar_t* file)
{
    __internals_shell32_shellexecute(file, L"edit", NULL);
}

METHOD bool libufm::Core::FileSystem::FileExists(const wchar_t* file)
{
    return PathFileExists(file);
}

METHOD bool libufm::Core::FileSystem::Move(const wchar_t* source, const wchar_t* dest, bool overwrite)
{
    if (overwrite)
    {
        return MoveFileEx(
            source, dest, MOVEFILE_REPLACE_EXISTING);
    }
    else
    {
        return MoveFile(
            source, dest);
    }
}

METHOD bool libufm::Core::FileSystem::IsDirectory(const wchar_t* path)
{
    return (
        GetFileAttributes(path) & FILE_ATTRIBUTE_DIRECTORY);
}

METHOD bool libufm::Core::FileSystem::IsFile(const wchar_t* path)
{
    return !IsDirectory(path);
}

METHOD bool libufm::Core::FileSystem::NewDirectory(const wchar_t* dir)
{
    return (CreateDirectory(dir, NULL) != 0);
}

METHOD void libufm::Core::FileSystem::PrintFile(const wchar_t* file)
{
    __internals_shell32_shellexecute(file, L"print", NULL);
}

METHOD bool libufm::Core::FileSystem::RecycleFile(const wchar_t* file)
{
    return RecycleFile(file, NULL);
}

METHOD bool libufm::Core::FileSystem::RecycleFile(const wchar_t* file, HWND window)
{
    SHFILEOPSTRUCT fileOp;

    ZeroMemory(
        &fileOp,
        sizeof(fileOp));

    fileOp.hwnd = window;
    fileOp.wFunc = FO_DELETE;
    fileOp.pFrom = file;
    fileOp.fFlags = FOF_ALLOWUNDO;
    fileOp.pTo = NULL;

    return (SHFileOperation(&fileOp) == 0);
}

METHOD void libufm::Core::FileSystem::RunElevated(const wchar_t* file)
{
    __internals_shell32_shellexecute(file, L"runas", NULL);
}

METHOD void libufm::Core::FileSystem::ShowFileProperties(const wchar_t* file)
{
    SHELLEXECUTEINFO info;

    ZeroMemory(
        &info,
        sizeof(info));

    info.cbSize = sizeof(info);
    info.fMask = SEE_MASK_INVOKEIDLIST;
    info.hwnd = NULL;
    info.lpVerb = L"properties";
    info.lpFile = file;
    info.lpParameters = NULL;
    info.lpDirectory = NULL;
    info.nShow = SW_SHOW;

    ShellExecuteEx(&info);
}

METHOD void libufm::Core::FileSystem::Start(const wchar_t* file)
{
    __internals_shell32_shellexecute(file, L"open", NULL);
}

METHOD void libufm::Core::FileSystem::Start(const wchar_t* file, const wchar_t* params)
{
    __internals_shell32_shellexecute(file, L"open", params);
}

void libufm::Core::FileSystem::__internals_shell32_shellexecute(const wchar_t* file, const wchar_t* operation, const wchar_t* params)
{
    SHELLEXECUTEINFO info;

    ZeroMemory(
        &info,
        sizeof(info));

    info.cbSize = sizeof(info);
    info.fMask = SEE_MASK_DEFAULT | SEE_MASK_NOCLOSEPROCESS;
    info.hwnd = NULL;
    info.lpVerb = operation;
    info.lpFile = file;
    info.lpParameters = params;
    info.lpDirectory = NULL;
    info.nShow = SW_SHOW;

    ShellExecuteEx(&info);
}
