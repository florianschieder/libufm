#pragma once

#include "String.h"
#include "../libufmdef.h"

#include <map>

namespace libufm
{
    namespace Core
    {
        namespace FileDetection
        {
            METHOD bool IsGdipSupportedImage(String& fileType);
            METHOD bool IsUnicode(String& filename);
            METHOD bool IsUnicode(FILE* fh);
            METHOD bool IsTextFile(String& filename);
            METHOD bool IsTextFile(FILE* fh);
            METHOD String MimeTypeFromString(String& extension);
        }
    }
}
