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

        virtual void setLayout(const BufferLayout &layout) override { mLayout = layout; };
        virtual const BufferLayout &getLayout() const override { return mLayout; };

    private:
        unsigned int mRendererId;
        BufferLayout mLayout;
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