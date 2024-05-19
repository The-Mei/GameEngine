#pragma once

#include "Renderer/Buffer.h"

namespace Hazel
{
    class HAZEL_API VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;
        virtual void unBind() const = 0;

        virtual void addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>> getVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer> getIndexBuffer() const = 0;

        static Ref<VertexArray> create();
    };
}