#pragma once

#include "Core.h"

#include "Window.h"

namespace Hazel
{
    class HAZEL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event &e);

    private:
        bool onWindowClose(class WindowCloseEvent &e);

    private:
        std::unique_ptr<Window> mWindow;
        bool mRunning;
    };

    // To be defined in client
    Application *createApplication();

}