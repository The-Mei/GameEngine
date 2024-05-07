#include "Hzpch.h"

#include "Renderer/Shader.h"

#include "Renderer/Renderer.h"

#include "OpenGlShader.h"

namespace Hazel
{

    Ref<Shader> Shader::create(const std::string &filepath)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::kOpenGl:
            return std::make_shared<OpenGlShader>(filepath);
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::kNone:
            HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        case RendererAPI::API::kOpenGl:
            return std::make_shared<OpenGlShader>(name, vertexSrc, fragmentSrc);
        }
        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    void ShaderLibrary::add(const std::string &name, const Ref<Shader> &shader)
    {
        HZ_CORE_ASSERT(!isExist(name), "Shader already exist");
        mShaders[name] = shader;
    }

    void ShaderLibrary::add(const Ref<Shader> &shader)
    {
        auto name = shader->getName();
        add(name, shader);
    }

    Ref<Shader> ShaderLibrary::load(const std::string &filepath)
    {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string &name, const std::string &filepath)
    {
        auto shader = Shader::create(filepath);
        add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::get(const std::string &name)
    {
        HZ_CORE_ASSERT(isExist(name), "Shader not find");
        return mShaders[name];
    }

    bool ShaderLibrary::isExist(const std::string &name)
    {
        return mShaders.find(name) != mShaders.end();
    }
}