
#include "texture_2d.hpp"

#include <glad/glad.h>

#include <cmath>

Texture2D::Texture2D(int width, int height, TextureFormat format, bool mipmap) :
format_(format), width_(width), height_(height), mipmap_(mipmap)
{
	glGenTextures(1, &id_);

	int bound_id = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_id);
	glBindTexture(GL_TEXTURE_2D, id_);
	
	int num_mipmaps = static_cast<int>(floor(log2(std::max(width, height)))) + 1;
	glTexStorage2D(GL_TEXTURE_2D, mipmap ? num_mipmaps : 1, GetInternalFormat(), width, height);
	set_filter(TextureFilter::kBilinear);

	glBindTexture(GL_TEXTURE_2D, bound_id);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &id_);
}

void Texture2D::CopyFrom(const void* src)
{
	int bound_id = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_id);
	glBindTexture(GL_TEXTURE_2D, id_);
	
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width_, height_, GetExternalFormat(), GetPixelComponentType(), src);
	if (mipmap_)
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, bound_id);
}

void Texture2D::Bind(unsigned int texture_unit)
{
	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(GL_TEXTURE_2D, id_);
}

TextureFormat Texture2D::format() const
{
	return format_;
}

int Texture2D::width() const
{
	return width_;
}

int Texture2D::height() const
{
	return height_;
}

bool Texture2D::mipmap() const
{
	return mipmap_;
}

void Texture2D::set_filter(TextureFilter filter)
{
	int bound_id = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_id);
	glBindTexture(GL_TEXTURE_2D, id_);

	int min_filter = mipmap_ ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
	int mag_filter = GL_NEAREST;
	switch (filter)
	{
	case TextureFilter::kPoint:
		min_filter = mipmap_ ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST;
		mag_filter = GL_NEAREST;
		break;

	case TextureFilter::kBilinear:
		min_filter = mipmap_ ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR;
		mag_filter = GL_LINEAR;
		break;

	case TextureFilter::kTrilinear:
		min_filter = mipmap_ ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
		mag_filter = GL_LINEAR;
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	filter_ = filter;

	glBindTexture(GL_TEXTURE_2D, bound_id);
}

TextureFilter Texture2D::filter() const
{
	return filter_;
}

void Texture2D::set_wrap(TextureWrap wrap)
{
	int bound_id = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &bound_id);
	glBindTexture(GL_TEXTURE_2D, id_);

	int wrap_value = GL_REPEAT;
	switch (wrap)
	{
	case TextureWrap::kRepeat:
		wrap_value = GL_REPEAT;
		break;

	case TextureWrap::kMirroredRepeat:
		wrap_value = GL_MIRRORED_REPEAT;
		break;

	case TextureWrap::kClamp:
		wrap_value = GL_CLAMP_TO_EDGE;
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_value);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_value);
	wrap_ = wrap;

	glBindTexture(GL_TEXTURE_2D, bound_id);
}

TextureWrap Texture2D::wrap() const
{
	return wrap_;
}

unsigned int Texture2D::GetExternalFormat() const
{
	switch (format_)
	{
	case TextureFormat::kRGB24:
		return GL_RGB;

	case TextureFormat::kBGR24:
		return GL_BGR;

	case TextureFormat::kRGBA32:
		return GL_RGBA;

	case TextureFormat::kBGRA32:
		return GL_BGRA;
	}

	return GL_INVALID_ENUM;
}

unsigned Texture2D::GetPixelComponentType() const
{
	switch (format_)
	{
	case TextureFormat::kRGB24:
	case TextureFormat::kBGR24:
	case TextureFormat::kRGBA32:
	case TextureFormat::kBGRA32:
		return GL_UNSIGNED_BYTE;
	}

	return GL_INVALID_ENUM;
}

unsigned int Texture2D::GetInternalFormat() const
{
	switch (format_)
	{
	case TextureFormat::kRGB24:
	case TextureFormat::kBGR24:
		return GL_RGB8;
	case TextureFormat::kRGBA32:
	case TextureFormat::kBGRA32:
		return GL_RGBA8;
	}

	return GL_INVALID_ENUM;
}
