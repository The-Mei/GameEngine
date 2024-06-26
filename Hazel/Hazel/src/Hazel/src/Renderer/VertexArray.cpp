#include "Hzpch.h"

#include "Renderer/VertexArray.h"

#include "Renderer/Renderer.h"

#include "OpenGlVertexArray.h"

namespace Hazel
{
    Ref<VertexArray> VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::kOpenGl:
            return std::make_shared<OpenGlVertexArray>();
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}