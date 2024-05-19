#include "Hzpch.h"

#include "OpenGlContext.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "GL/gl.h"

namespace Hazel
{

    OpenGlContext::OpenGlContext(class GLFWwindow *windowHandle)
        : mWindowHandle(windowHandle)
    {
        HZ_CORE_ASSERT(windowHandle, "Window handle is nullptr");
    }

    void OpenGlContext::init()
    {
        glfwMakeContextCurrent(mWindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        HZ_CORE_ASSERT(status, "Failed tp init Glad");

        LOGI("OpenGl Info:");
        LOGTMP(" Verdor: %s", glGetString(GL_VENDOR));
        LOGTMP(" Renderer: %s", glGetString(GL_RENDERER));
        LOGTMP(" Version: %s", glGetString(GL_VERSION));
        // LOGI("OpenGl RendererL {0}", glGetString(GL_VENDOR));
    }

    void OpenGlContext::swapBuffers()
    {
        glfwSwapBuffers(mWindowHandle);
    }
}