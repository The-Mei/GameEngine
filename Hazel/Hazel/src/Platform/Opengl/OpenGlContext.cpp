#include "Hzpch.h"

#include "OpenGlContext.h"

#include "GL/Gl.h"

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
    }

    void OpenGlContext::swapBuffers()
    {
        glfwSwapBuffers(mWindowHandle);
    }
}