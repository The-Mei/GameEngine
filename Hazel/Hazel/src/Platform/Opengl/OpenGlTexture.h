#pragma once

#include "Renderer/Texture.h"

namespace Hazel
{
    class HAZEL_API OpenGlTexture2D : public Texture2D
    {
    public:
        OpenGlTexture2D(uint32_t width, uint32_t height);
        OpenGlTexture2D(const std::string &path);
        virtual ~OpenGlTexture2D();

        virtual uint32_t getWidth() const override { return mWidth; }
        virtual uint32_t getHeight() const override { return mHeight; }

        virtual void bind(uint32_t slot = 0) const override;
        virtual void unBind() const override;

        virtual void setData(void *data, uint32_t size) override;

    private:
        std::string mPath;
        uint32_t mWidth;
        uint32_t mHeight;
        uint32_t mRendererId;
        uint32_t mInternalformat, mDataFormat;
    };
}