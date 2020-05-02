#include <core/FileDetection.h>

METHOD String libufm::Core::FileDetection::MimeTypeFromString(const String& extension)
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

    if (extension == L"exe" || extension == L"cab" || extension == L"msi" || extension == L"dll" || extension == L"zip")
    {
        return L"binary";
    }

    return L"unknown";
}

METHOD bool libufm::Core::FileDetection::IsGdipSupportedImage(const String& fileType)
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

METHOD bool libufm::Core::FileDetection::IsUnicode(const String& filename)
{
    FILE* fp;
    bool isUnicode;
    
    _wfopen_s(
        &fp,
        filename.c_str(),
        L"r+b");

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
