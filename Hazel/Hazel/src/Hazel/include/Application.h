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

    private:
        std::unique_ptr<Window> mWindow;
    };

    // To be defined in client
    Application *createApplication();

}