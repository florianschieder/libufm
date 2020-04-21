#pragma once

#include "String.h"
#include "../libufmdef.h"

namespace libufm
{
    namespace FileType
    {
        METHOD String MimeTypeFromString(const String& extension);
        METHOD bool IsGdipSupportedImage(const String& fileType);
    }
}
