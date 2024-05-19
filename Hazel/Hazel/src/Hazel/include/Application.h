#pragma once

#include "Core/Core.h"

#include "Core/Window.h"
#include "Layer/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

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

        inline static Application &get() { return *gInstance; }
        inline Window &getWindow() { return *mWindow; }

    private:
        bool onWindowClose(class WindowCloseEvent &e);
        bool onWindowResize(class WindowResizeEvent &e);

    private:
        std::unique_ptr<Window> mWindow;
        ImGuiLayer *mImGuiLayer;
        bool mRunning;
        bool mMinimized;
        LayerStack mLayerStack;
        float mLastFrameTime = 0.0f;

        static Application *gInstance;
    };

    // To be defined in client
    Application *createApplication();

}