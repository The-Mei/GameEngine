#include "OpenGlTexture.h"

#include "Hzpch.h"

#include "stb_image.h"
#include "glad/glad.h"
#include "Renderer/GlCheckError.h"

namespace Hazel
{

    OpenGlTexture2D::OpenGlTexture2D(const std::string &path)
        : mPath(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        HZ_CORE_ASSERT(data, "Failed to load image!");

        mWidth = width;
        mHeight = height;

        GLCHECK(glCreateTextures(GL_TEXTURE_2D, 1, &mRendererId));
        GLCHECK(glTextureStorage2D(mRendererId, 1, GL_RGB8, mWidth, mHeight));

        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCHECK(glTextureParameteri(mRendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

        GLCHECK(glTextureSubImage2D(mRendererId, 0, 0, 0, mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, data));

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
}