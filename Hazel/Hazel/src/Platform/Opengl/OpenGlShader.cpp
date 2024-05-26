#include "OpenGlShader.h"

#include <fstream>

#include "GlCheckError.h"

#include "Core/Log.h"

#include "gtc/type_ptr.hpp"

namespace Hazel
{
    static unsigned int ShaderTypeFromString(const std::string &type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        HZ_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    OpenGlShader::OpenGlShader(const std::string &filepath)
    {
        std::string source = readFile(filepath);
        auto shaderSources = preProcess(source);
        compile(shaderSources);

        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind(".");
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;

        mName = filepath.substr(lastSlash, count);
    }

    OpenGlShader::OpenGlShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc)
        : mName(name)
    {
        std::unordered_map<unsigned int, std::string> shaderSources;
        shaderSources[GL_VERTEX_SHADER] = vertexSrc;
        shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
        compile(shaderSources);
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

    void OpenGlShader::setInt(const std::string &name, const int &value)
    {
        setUniform1i(name, value);
    }

    void OpenGlShader::setFloat3(const std::string &name, const glm::vec3 &value)
    {
        setUniform3f(name, value);
    }

    void OpenGlShader::setFloat4(const std::string &name, const glm::vec4 &value)
    {
        setUniform4f(name, value);
    }

    void OpenGlShader::setMat4(const std::string &name, const glm::mat4 &value)
    {
        setUniformMatrix4fv(name, value);
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

    //     std::string OpenGlShader::readShaderSource(const std::string &filepath)
    //     {
    // #if 1
    //         std::ifstream fileStream(filepath, std::ios::in);
    //         std::string line{};
    //         std::stringstream ss;
    //         while (getline(fileStream, line))
    //         {
    //             ss << line << "\n";
    //         }
    // #else
    //         std::ifstream shaderFile;
    //         shaderFile.exception(std::ifstream::failbit | std::ifstream::badbit);
    //         try
    //         {
    //             shaderFile.open(filepath.c_str());
    //             std::stringstream ss;
    //             ss << shaderFile.rdbuf();
    //             shaderFile.close();
    //         }
    //         catch (std::ifstream::failure &e)
    //         {
    //         }

    // #endif

    //         return ss.str();
    //     }

    std::string OpenGlShader::readFile(const std::string &filepath)
    {
        std::ifstream in(filepath, std::ios::in | std::ios::binary);
        std::string result;
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            LOGE("Could not open file {0}", filepath);
        }
        return result;
    }

    std::unordered_map<unsigned int, std::string> OpenGlShader::preProcess(const std::string &source)
    {
        std::unordered_map<unsigned int, std::string> shaderSources;

        const char *typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find_first_of(typeToken, 0);

        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            HZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void OpenGlShader::compile(const std::unordered_map<unsigned int, std::string> &shaderSources)
    {
        unsigned int program = glCreateProgram();
        std::vector<unsigned int> shaderIds;
        for (auto &[type, source] : shaderSources)
        {
            unsigned int shader = glCreateShader(type);
            const char *shaderSrc = source.c_str();
            GLCHECK(glShaderSource(shader, 1, &shaderSrc, nullptr));
            GLCHECK(glCompileShader(shader));
            int isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                int maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<char> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                LOGE("{0}", infoLog.data());
                HZ_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }
            GLCHECK(glAttachShader(program, shader));
            shaderIds.push_back(shader);
        }

        GLCHECK(glLinkProgram(program));
        GLCHECK(glValidateProgram(program));

        int linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &linked);
        if (linked == GL_FALSE)
        {
            int maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            for (auto &shader : shaderIds)
                glDeleteShader(shader);

            LOGE("{0}", infoLog.data());
            HZ_CORE_ASSERT(false, "Program Link failure!");
            return;
        }

        for (auto &shader : shaderIds)
            glDeleteShader(shader);

        mProgramId = program;
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