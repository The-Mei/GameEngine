#include "Application.h"

#include <GLFW/glfw3.h>

#include "Events/ApplicationEvent.h"
namespace Hazel
{
    Application::Application() : mRunning(false)
    {
        mWindow = std::unique_ptr<Window>(Window::create());
        mWindow->setEventCallback(HZ_BIND_EVENT_FN(onEvent));
        mRunning = true;
    }

    Application::~Application() {}

    void Application::onEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(onWindowClose));
        LOGT("{0}", e);
    }

    void Application::run()
    {
        while (mRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            mWindow->onUpdate();
        }
    }

    bool Application::onWindowClose(class WindowCloseEvent &e)
    {
        mRunning = false;
        return true;
    }
}