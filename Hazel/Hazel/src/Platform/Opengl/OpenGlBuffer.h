#pragma once

#include "Renderer/Buffer.h"

namespace Hazel
{
    class OpenGlVertexBuffer : public VertexBuffer
    {
    public:
        OpenGlVertexBuffer(float *vertices, uint32_t size);
        virtual ~OpenGlVertexBuffer();

        virtual void bind() const override;
        virtual void unBind() const override;

    private:
        unsigned int mRendererId;
    };

    class OpenGlIndexBuffer : public IndexBuffer
    {
    public:
        OpenGlIndexBuffer(uint32_t *indices, uint32_t count);
        virtual ~OpenGlIndexBuffer();

        virtual void bind() const override;
        virtual void unBind() const override;

        virtual uint32_t getCount() const { return mCount; };

    private:
        unsigned int mRendererId;
        uint32_t mCount;
    };

}