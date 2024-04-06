#include "Hzpch.h"

#include "Renderer/VertexArray.h"

#include "Renderer/Renderer.h"

#include "OpenGlVertexArray.h"

namespace Hazel
{
    VertexArray *VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::kOpenGl:
            return new OpenGlVertexArray();
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}