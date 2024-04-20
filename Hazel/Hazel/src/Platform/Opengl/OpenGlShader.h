#pragma once

#include <string>
#include <unordered_map>

#include "Renderer/Shader.h"

#include "glm.hpp"

namespace Hazel
{
    class HAZEL_API OpenGlShader : public Shader
    {
    public:
        OpenGlShader(const std::string vertexPath, const std::string fragmentPath);
        virtual ~OpenGlShader();
        void bind();
        void unBind();
        unsigned int getProgramId() { return mProgramId; }

        void setUniform1i(const std::string &name, int value);
        void setUniform1f(const std::string &name, float value);
        void setUniform2f(const std::string &name, const glm::vec2 &value);
        void setUniform3f(const std::string &name, const glm::vec3 &value);
        void setUniform4f(const std::string &name, const glm::vec4 &value);
        void setUniformMatrix3fv(const std::string &name, const glm::mat3 &value);
        void setUniformMatrix4fv(const std::string &name, const glm::mat4 &value);

    private:
        std::string readShaderSource(const std::string &filepath);
        unsigned int compileShader(unsigned int type, const std::string &source);
        unsigned int createShaderProgram(const std::string &vertexSource, const std::string &fragmentSource);
        unsigned int getUniformId(const std::string name);

    private:
        unsigned int mProgramId;
        std::unordered_map<std::string, unsigned int> mUniform;
    };
}