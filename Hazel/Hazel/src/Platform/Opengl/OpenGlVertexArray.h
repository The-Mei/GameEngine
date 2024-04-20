#pragma once

#include "Renderer/VertexArray.h"

namespace Hazel
{
    class OpenGlVertexArray : public VertexArray
    {
    public:
        OpenGlVertexArray();
        virtual ~OpenGlVertexArray();

        virtual void bind() const override;
        virtual void unBind() const override;

        virtual void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
        virtual void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

        virtual const std::vector<Ref<VertexBuffer>> getVertexBuffers() const { return mVertexBuffer; };
        virtual const Ref<IndexBuffer> getIndexBuffer() const { return mIndexBuffer; }

    private:
        unsigned int mRendererId;
        std::vector<Ref<VertexBuffer>> mVertexBuffer;
        Ref<IndexBuffer> mIndexBuffer;
    };

}