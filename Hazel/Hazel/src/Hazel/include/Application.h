#pragma once

#include "Core.h"

#include "Window.h"
#include "Layer/LayerStack.h"

namespace Hazel
{
    class HAZEL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event &e);

        void pushLayer(Layer *layer);
        void pushOverlay(Layer *overlay);

    private:
        bool onWindowClose(class WindowCloseEvent &e);

    private:
        std::unique_ptr<Window> mWindow;
        bool mRunning;
        LayerStack mLayerStack;
    };

    // To be defined in client
    Application *createApplication();

}