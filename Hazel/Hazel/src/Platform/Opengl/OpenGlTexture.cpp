#include "OpenGlTexture.h"

#include "Hzpch.h"

#include "stb_image.h"
#include "glad/glad.h"
#include "GlCheckError.h"

namespace Hazel
{
    OpenGlTexture2D::OpenGlTexture2D(uint32_t width, uint32_t height)
        : mWidth(width), mHeight(height)
    {

        mInternalformat = GL_RGBA8;
        mDataFormat = GL_RGBA;
        GLCHECK(glCreateTextures(GL_TEXTURE_2D, 1, &mRendererId));
        GLCHECK(glTextureStorage2D(mRendererId, 1, mInternalformat, mWidth, mHeight));

        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_WRAP_T, GL_REPEAT));
    }

    OpenGlTexture2D::OpenGlTexture2D(const std::string &path)
        : mPath(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        HZ_CORE_ASSERT(data, "Failed to load image!");

        mWidth = width;
        mHeight = height;

        GLenum internalformat, dataFormat = 0;
        if (channels == 4)
        {
            internalformat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalformat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        HZ_CORE_ASSERT(internalformat && dataFormat, "Invalid image format!");

        mInternalformat = internalformat;
        mDataFormat = dataFormat;

        GLCHECK(glCreateTextures(GL_TEXTURE_2D, 1, &mRendererId));
        GLCHECK(glTextureStorage2D(mRendererId, 1, internalformat, mWidth, mHeight));

        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_WRAP_S, GL_REPEAT));
        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_WRAP_T, GL_REPEAT));

        GLCHECK(glTextureSubImage2D(mRendererId, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data));

        stbi_image_free(data);
    }

    OpenGlTexture2D::~OpenGlTexture2D()
    {
        glDeleteTextures(1, &mRendererId);
    }

    void OpenGlTexture2D::bind(uint32_t slot) const
    {
        GLCHECK(glBindTextureUnit(slot, mRendererId));
    }

    void OpenGlTexture2D::unBind() const
    {
        GLCHECK(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void OpenGlTexture2D::setData(void *data, uint32_t size)
    {
        uint32_t bpp = mDataFormat == GL_RGBA ? 4 : 3;
        HZ_CORE_ASSERT(size == mWidth * mHeight * bpp, "Data must be entire texture!");
        GLCHECK(glTextureSubImage2D(mRendererId, 0, 0, 0, mWidth, mHeight, mDataFormat, GL_UNSIGNED_BYTE, data));
    }
}