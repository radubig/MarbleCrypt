#include "Exceptions.h"

ResourceLoadException::ResourceLoadException(const std::string& filePath, const std::string& fileType)
    : std::runtime_error(fileType + " \"" + filePath + "\" could not be loaded!") {}

FontLoadException::FontLoadException(const std::string& filePath)
    : ResourceLoadException(filePath, "Font") {}

TextureLoadException::TextureLoadException(const std::string& filePath)
    : ResourceLoadException(filePath, "Texture") {}