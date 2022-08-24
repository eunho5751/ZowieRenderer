#pragma once

#include "texture_consts.hpp"

class Texture2D
{
public:
    Texture2D(int width, int height, TextureFormat format, bool mipmap);
    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D(Texture2D&&) = delete;
    Texture2D operator=(const Texture2D&) = delete;
    Texture2D operator=(Texture2D&&) = delete;

    void CopyFrom(const void* src);
    void Bind(unsigned int texture_unit);

    TextureFormat format() const;
    int width() const;
    int height() const;
    bool mipmap() const;

    void set_filter(TextureFilter filter);
    TextureFilter filter() const;

    void set_wrap(TextureWrap wrap);
    TextureWrap wrap() const;

private:
    unsigned int GetExternalFormat() const;
    unsigned int GetPixelComponentType() const;
    unsigned int GetInternalFormat() const;

private:
    unsigned int id_;
    TextureFormat format_;
    int width_;
    int height_;
    bool mipmap_;
    TextureFilter filter_;
    TextureWrap wrap_;
};