#include "Hzpch.h"

#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"

#include "OpenGlShader.h"

namespace Hazel
{

    Shader *Shader::create(const std::string &filepath)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::kOpenGl:
            return new OpenGlShader(filepath);
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Shader *Shader::create(const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::kOpenGl:
            return new OpenGlShader(vertexSrc, fragmentSrc);
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}