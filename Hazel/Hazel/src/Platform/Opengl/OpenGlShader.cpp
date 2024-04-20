#include "OpenGlShader.h"

#include <fstream>
#include <sstream>

#include "Renderer/GlCheckError.h"

#include "Log.h"

#include "gtc/type_ptr.hpp"

namespace Hazel
{

    OpenGlShader::OpenGlShader(const std::string vertexPath, const std::string fragmentPath)
    {
        // std::string vertex = readShaderSource(vertexPath);
        // std::string fragement = readShaderSource(fragmentPath);
        // mProgramId = createShaderProgram(vertex, fragement);
        mProgramId = createShaderProgram(vertexPath, fragmentPath);
    }

    OpenGlShader::~OpenGlShader()
    {
        GLCHECK(glDeleteProgram(mProgramId));
    }

    void OpenGlShader::bind()
    {
        GLCHECK(glUseProgram(mProgramId));
    }

    void OpenGlShader::unBind()
    {
        GLCHECK(glUseProgram(0));
    }

    void OpenGlShader::setUniform1i(const std::string &name, int value)
    {
        GLCHECK(glUniform1i(getUniformId(name), value));
    }

    void OpenGlShader::setUniform1f(const std::string &name, float value)
    {
        GLCHECK(glUniform1f(getUniformId(name), value));
    }

    void OpenGlShader::setUniform2f(const std::string &name, const glm::vec2 &value)
    {
        GLCHECK(glUniform2f(getUniformId(name), value.x, value.y));
    }

    void OpenGlShader::setUniform3f(const std::string &name, const glm::vec3 &value)
    {
        GLCHECK(glUniform3f(getUniformId(name), value.x, value.y, value.z));
    }

    void OpenGlShader::setUniform4f(const std::string &name, const glm::vec4 &value)
    {
        GLCHECK(glUniform4f(getUniformId(name), value.x, value.y, value.z, value.w));
    }

    void OpenGlShader::setUniformMatrix3fv(const std::string &name, const glm::mat3 &value)
    {
        GLCHECK(glUniformMatrix3fv(getUniformId(name), 1, GL_FALSE, glm::value_ptr(value)));
    }

    void OpenGlShader::setUniformMatrix4fv(const std::string &name, const glm::mat4 &value)
    {
        GLCHECK(glUniformMatrix4fv(getUniformId(name), 1, GL_FALSE, glm::value_ptr(value)));
    }

    std::string OpenGlShader::readShaderSource(const std::string &filepath)
    {
#if 1
        std::ifstream fileStream(filepath, std::ios::in);
        std::string line{};
        std::stringstream ss;
        while (getline(fileStream, line))
        {
            ss << line << "\n";
        }
#else
        std::ifstream shaderFile;
        shaderFile.exception(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            shaderFile.open(filepath.c_str());
            std::stringstream ss;
            ss << shaderFile.rdbuf();
            shaderFile.close();
        }
        catch (std::ifstream::failure &e)
        {
        }

#endif

        return ss.str();
    }

    unsigned int OpenGlShader::compileShader(unsigned int type, const std::string &source)
    {
        LOGI("{0}, {1}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), source.c_str());
        unsigned int shader = glCreateShader(type);
        const char *shaderSrc = source.c_str();
        GLCHECK(glShaderSource(shader, 1, &shaderSrc, nullptr));
        GLCHECK(glCompileShader(shader));

        int result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (!result)
        { // NOLINT
            printShaderLog(type, shader);
            glDeleteShader(shader);
        }
        return shader;
    }

    unsigned int OpenGlShader::createShaderProgram(const std::string &vertexSource, const std::string &fragmentSource)
    {
        unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
        unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
        unsigned int program = glCreateProgram();
        GLCHECK(glAttachShader(program, vertex));
        GLCHECK(glAttachShader(program, fragment));
        GLCHECK(glLinkProgram(program));
        GLCHECK(glValidateProgram(program));

        int linked;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (!linked)
        {
            printProgramLog(program);
            glDeleteProgram(program);
            return 0;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return program;
    }

    unsigned int OpenGlShader::getUniformId(const std::string name)
    {
        auto it = mUniform.find(name);
        if (it != mUniform.end())
            return it->second;
        else
        {
            GLCHECK(unsigned int id = glGetUniformLocation(mProgramId, name.c_str()));
            mUniform.emplace(std::pair<std::string, unsigned int>(name, id));
            return id;
        }
    }
}