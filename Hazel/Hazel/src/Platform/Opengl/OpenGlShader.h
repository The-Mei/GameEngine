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
        OpenGlShader(const std::string &filepath);
        OpenGlShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
        virtual ~OpenGlShader();
        virtual void bind() override;
        virtual void unBind() override;
        virtual const std::string &getName() const override { return mName; }
        unsigned int getProgramId() { return mProgramId; }

        virtual void setInt(const std::string &name, const int &value) override;
        virtual void setFloat3(const std::string &name, const glm::vec3 &value) override;
        virtual void setFloat4(const std::string &name, const glm::vec4 &value) override;
        virtual void setMat4(const std::string &name, const glm::mat4 &value) override;

        void setUniform1i(const std::string &name, int value);
        void setUniform1f(const std::string &name, float value);
        void setUniform2f(const std::string &name, const glm::vec2 &value);
        void setUniform3f(const std::string &name, const glm::vec3 &value);
        void setUniform4f(const std::string &name, const glm::vec4 &value);
        void setUniformMatrix3fv(const std::string &name, const glm::mat3 &value);
        void setUniformMatrix4fv(const std::string &name, const glm::mat4 &value);

    private:
        std::string readFile(const std::string &filepath);
        std::unordered_map<unsigned int, std::string> preProcess(const std::string &source);
        void compile(const std::unordered_map<unsigned int, std::string> &shaderSources);
        unsigned int compileShader(unsigned int type, const std::string &source);
        unsigned int createShaderProgram(const std::string &vertexSource, const std::string &fragmentSource);
        unsigned int getUniformId(const std::string name);

    private:
        unsigned int mProgramId;
        std::string mName;
        std::unordered_map<std::string, unsigned int> mUniform;
    };
}