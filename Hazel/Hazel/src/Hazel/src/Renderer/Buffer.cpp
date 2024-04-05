#include "Hzpch.h"

#include "Renderer/Buffer.h"

#include "Renderer/Renderer.h"

#include "OpenGlBuffer.h"

namespace Hazel
{
    VertexBuffer *VertexBuffer::create(float *vertices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::kOpenGl:
            return new OpenGlVertexBuffer(vertices, size);
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    IndexBuffer *IndexBuffer::create(uint32_t *indices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::kOpenGl:
            return new OpenGlIndexBuffer(indices, size);
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}