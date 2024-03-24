#include "WindowsWindow.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
// #include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
    static bool gGLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char *description)
    {
        LOGE("GLFW Error ({0}) : {1}", error, description);
    }

    Window *Window::create(const WindowProps &props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps &props)
    {
        init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        shutdown();
    }

    void WindowsWindow::init(const WindowProps &props)
    {
        mData.title = props.title;
        mData.width = props.width;
        mData.height = props.height;
        LOGI("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!gGLFWInitialized)
        {
            int success = glfwInit();
            LOGI("GLFW init : {0}", success);
            HZ_CORE_ASSERT(success, "Could not intialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            gGLFWInitialized = true;
        }

        mWindow = glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(mWindow);
        // int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        // HZ_CORE_ASSERT(status, "Failed tp init Glad");
        glfwSetWindowUserPointer(mWindow, &mData);
        setVSync(true);

        glfwSetWindowSizeCallback(mWindow,
                                  [](GLFWwindow *window, int width, int height)
                                  { 
                                    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                    data.width = width;
                                    data.height = height;
                                    WindowResizeEvent event(width, height);
                                    data.eventCallback(event); });

        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow *window)
                                   {
                                    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                    WindowCloseEvent event;
                                    data.eventCallback(event); });

        glfwSetKeyCallback(mWindow, [](GLFWwindow *window, int key, int scancode, int action, int modss)
                           {
                            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                               switch (action)
                               {
                               case GLFW_PRESS:
                               {
                                   KeyPressedEvent event(key, 0);
                                   data.eventCallback(event);
                               }
                               break;
                               case GLFW_RELEASE:
                               {
                                   KeyReleasedEvent event(key);
                                   data.eventCallback(event);
                               }
                               break;
                               case GLFW_REPEAT:
                               {
                                   KeyPressedEvent event(key, 1);
                                   data.eventCallback(event);
                               }
                               break;
                               } });

        glfwSetCharCallback(mWindow, [](GLFWwindow *window, unsigned int keyCode)
                            { WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                             KeyTypedEvent event(keyCode);
                             data.eventCallback(event); });
        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow *window, int button, int action, int mods)
                                   {
                                    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                    switch(action)
                                    {
                                        case GLFW_PRESS:
                                        {
                                            MouseButtonPressedEvent event(button);
                                            data.eventCallback(event);
                                        }
                                        break;
                                        case GLFW_RELEASE:
                                        {
                                            MouseButtonReleasedEvent event(button);
                                            data.eventCallback(event);
                                        }
                                        break;
                                    } });

        glfwSetScrollCallback(mWindow,
                              [](GLFWwindow *window, double xOffSet, double yOffSet)
                              {
                                WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                MouseScrolledEvent event((float)xOffSet, (float)yOffSet);
                                data.eventCallback(event); });

        glfwSetCursorPosCallback(mWindow,
                                 [](GLFWwindow *window, double xPos, double yPos)
                                 {
                                    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
                                    MouseMovedEvent event((float)xPos, (float)yPos);
                                    data.eventCallback(event); });
    }

    void WindowsWindow::shutdown()
    {
        glfwDestroyWindow(mWindow);
    }

    void WindowsWindow::onUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }

    void WindowsWindow::setVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        mData.vsync = enabled;
    }

    bool WindowsWindow::isVSync() const
    {
        return mData.vsync;
    }
}