#pragma once

enum class TextureFilter
{
    kPoint,
    kBilinear,
    kTrilinear
};

enum class TextureWrap
{
    kRepeat,
    kMirroredRepeat,
    kClamp
};

enum class TextureFormat
{
    kRGB24,
    kRGBA32,
    kBGR24,
    kBGRA32
};
