#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{
    class OpenGlContext : public GraphicsContext
    {
    public:
        OpenGlContext(GLFWwindow *windowHandle);

        virtual void init() override;
        virtual void swapBuffers() override;

    private:
        GLFWwindow *mWindowHandle;
    };

}