#include <core/FileType.h>

METHOD String libufm::FileType::MimeTypeFromString(const String& extension)
{
    if (IsGdipSupportedImage(extension))
    {
        return L"image";
    }

    if (extension == L"txt" || extension == L"log" || extension == L"rtf" || extension == L"ini"
        || extension == L"html" || extension == L"htm" || extension == L"js" || extension == L"css"
        || extension == L"c" || extension == L"cpp" || extension == L"cxx" || extension == L"h" || extension == L"hpp")
    {
        return L"text";
    }

    return L"unknown";
}

METHOD bool libufm::FileType::IsGdipSupportedImage(const String& fileType)
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
