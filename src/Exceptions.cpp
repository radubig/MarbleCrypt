#include "Exceptions.h"
#include <string>

ResourceLoadException::ResourceLoadException(const std::string& filePath, const std::string& fileType)
    : std::runtime_error(fileType + " \"" + filePath + "\" could not be loaded!") {}

ResourceLoadException::ResourceLoadException(const std::string& filePath)
    : std::runtime_error("File \"" + filePath + "\" could not be loaded!") {}

FontLoadException::FontLoadException(const std::string& filePath)
    : ResourceLoadException(filePath, "Font") {}

TextureLoadException::TextureLoadException(const std::string& filePath)
    : ResourceLoadException(filePath, "Texture") {}