#pragma once

#include <string>

namespace Hazel
{
    class HAZEL_API Shader
    {
    public:
        ~Shader() = default;
        virtual void bind() = 0;
        virtual void unBind() = 0;

        static Shader *create(const std::string vertexPath, const std::string fragmentPath);
    };
}