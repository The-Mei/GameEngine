#pragma once

#include "Core.h"

#include "Window.h"
#include "Layer/LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

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

    private:
        std::unique_ptr<Window> mWindow;
        ImGuiLayer *mImGuiLayer;
        bool mRunning;
        LayerStack mLayerStack;

        std::shared_ptr<Shader> mShader;
        std::shared_ptr<VertexArray> mVertexArray;

        std::shared_ptr<Shader> mBlueShader;
        std::shared_ptr<VertexArray> mSquareVA;
        static Application *gInstance;
    };

    // To be defined in client
    Application *createApplication();

}