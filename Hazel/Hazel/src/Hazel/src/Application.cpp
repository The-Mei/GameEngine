#include "Application.h"

namespace Hazel
{
    Application::Application()
    {
        mWindow = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application() {}

    void Application::run()
    {
        while (true)
        {
            mWindow->onUpdate();
        }
    }
}