#include <core/FileDetection.h>

METHOD String libufm::Core::FileDetection::MimeTypeFromString(String& extension)
{
    HKEY hKey = NULL;

    if (extension[0] != L'.')
    {
        std::wstring extensionCopy = L".";
        extensionCopy.append(extension);

        extension = extensionCopy;
    }

    std::wstring szResult = L"application/unknown";

    if (RegOpenKeyEx(HKEY_CLASSES_ROOT, extension.c_str(),
        0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        wchar_t szBuffer[256] = { 0 };
        DWORD dwBuffSize = sizeof(szBuffer);

        if (RegQueryValueEx(hKey, L"Content Type", NULL, NULL,
            (LPBYTE)szBuffer, &dwBuffSize) == ERROR_SUCCESS)
        {
            szResult = szBuffer;
        }

        RegCloseKey(hKey);
    }

    return szResult;
}

METHOD bool libufm::Core::FileDetection::IsGdipSupportedImage(String& fileType)
{
    return (fileType == L"bmp" ||
        fileType == L"dib" ||
        fileType == L"ico" ||
        fileType == L"gif" ||
        fileType == L"jpg" ||
        fileType == L"jpeg" ||
        fileType == L"png" ||
        fileType == L"tiff" ||
        fileType == L"wmf" ||
        fileType == L"emf");
}

METHOD bool libufm::Core::FileDetection::IsUnicode(String& filename)
{
    FILE* fp;
    bool isUnicode;
    
    _wfopen_s(
        &fp,
        filename.c_str(),
        L"rb");

    isUnicode = IsUnicode(fp);

    fclose(fp);

    return isUnicode;
}

METHOD bool libufm::Core::FileDetection::IsUnicode(FILE* fh)
{
    char buf[2];

    fread_s(
        buf,
        2,
        1,
        2,
        fh);
    rewind(fh);

    return (buf[0] == ((char) 0xFF)
         && buf[1] == ((char)0xFE));
}

METHOD bool libufm::Core::FileDetection::IsTextFile(String& filename)
{
    FILE* fp;
    bool isTextFile = true;

    _wfopen_s(
        &fp,
        filename.c_str(),
        L"rb");

    if (fp != 0)
    {
        isTextFile = IsTextFile(fp);
        fclose(fp);
    }

    return isTextFile;
}

METHOD bool libufm::Core::FileDetection::IsTextFile(FILE* fh)
{
    char buf[512];

    size_t readCharacters = fread_s(
        buf,
        sizeof(buf),
        sizeof(char),
        (size_t)512U,
        fh);

    rewind(fh);
    
    for (size_t i = 0; i < readCharacters; i++)
    {
        // Heuristic analysis if there are characters untypical for a
        // plain text file

        if (buf[i] != '\r' && buf[i] != '\n' // Line breaks
            && !((buf[i] >= 20) && (buf[i] <= 126))) // "Regular" characters
        {
            return false;
        }
    }

    return true;
}
