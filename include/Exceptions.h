#ifndef MARBLECRYPT_EXCEPTIONS_H
#define MARBLECRYPT_EXCEPTIONS_H

#include <stdexcept>

class ResourceLoadException: public std::runtime_error
{
public:
    explicit ResourceLoadException(const std::string& filePath, const std::string& fileType);
    explicit ResourceLoadException(const std::string& filePath);
};

class FontLoadException: public ResourceLoadException
{
public:
    explicit FontLoadException(const std::string& filePath);
};

class TextureLoadException : public ResourceLoadException
{
public:
    explicit TextureLoadException(const std::string& filePath);
};

#endif //MARBLECRYPT_EXCEPTIONS_H
