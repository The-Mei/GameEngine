#include "Renderer/Texture.h"

#include "Hzpch.h"

#include "Renderer/Renderer.h"

#include "OpenGlTexture.h"

namespace Hazel
{
    Ref<Texture2D> Texture2D::create(const std::string &path)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::kOpenGl:
            return std::make_shared<OpenGlTexture2D>(path);
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}
