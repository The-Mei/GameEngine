#pragma once

#include <string>

#include "glad/glad.h"

#include "Core/Log.h"

#ifdef LOG_MODULE_TAG
#undef LOG_MODULE_TAG
#endif
#define LOG_MODULE_TAG "GlCheckError"

#define ASSERT(x) \
    if (!x)       \
        __debugbreak();

#ifdef VERSION_DEBUG
#define GLCHECK(x)  \
    glClearError(); \
    x;              \
    ASSERT(glErrorLog(#x, __FILE__, __LINE__))
#else
#define GLCHECK(x) x
#endif

inline void glClearError()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

inline bool glErrorLog(const char *function, const char *file, int line)
{
    while (auto error = glGetError())
    {
        std::string errorInfo;
        switch (error)
        {
        case GL_INVALID_ENUM:
            errorInfo = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            errorInfo = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            errorInfo = "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            errorInfo = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            errorInfo = "GL_OUT_OF_MEMORY";
            break;
        default:
            errorInfo = "Unknow Error";
            break;
        }
        LOGI("[OpenGL Error] ({0} : {1}): {2} {3} {4}", error, errorInfo.c_str(), function, file, line);
        return false;
    }
    return true;
}

inline void printProgramLog(int prog)
{
    int length;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &length);
    if (length > 1)
    {
        char *log = new char[length];
        glGetProgramInfoLog(prog, length, &length, log);
        LOGI("failed to link program :{0}", log);
        delete log;
    }
}

inline void printShaderLog(unsigned int type, unsigned int shader)
{
    int length = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    if (length > 1)
    {
        char *log = new char[length];
        glGetShaderInfoLog(shader, length, &length, log);
        LOGI("{0} shader failed to compile, {1}", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), log);
        delete log;
    }
}