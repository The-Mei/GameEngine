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

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) override;
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const { return mVertexBuffer; };
        virtual const std::shared_ptr<IndexBuffer> getIndexBuffer() const { return mIndexBuffer; }

    private:
        unsigned int mRendererId;
        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffer;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };

}