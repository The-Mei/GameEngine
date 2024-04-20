#include "Hzpch.h"

#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"

#include "OpenGlShader.h"

namespace Hazel
{
    Shader *Shader::create(const std::string vertexPath, const std::string fragmentPath)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::kOpenGl:
            return new OpenGlShader(vertexPath, fragmentPath);
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}