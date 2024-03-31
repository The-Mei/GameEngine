#include "Hzpch.h"

#include "WindowsInput.h"

#include "glfw/glfw3.h"
#include "Application.h"

namespace Hazel
{
    Input *Input::gInstance = new WindowsInput();
    bool WindowsInput::isKeyPressedImpl(int keyCode)
    {
        auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::isMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::getMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getNativeWindow());
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        return {(float)xPos, (float)yPos};
    }

    float WindowsInput::getMouseXImpl()
    {
        auto [xPos, _] = getMousePositionImpl();
        return xPos;
        // c++17 以下
        //  auto v =  getMousePositionImpl();
        //  return std::get<0>(v);
    }

    float WindowsInput::getMouseYImpl()
    {
        auto [_, yPos] = getMousePositionImpl();
        return yPos;
    }
}