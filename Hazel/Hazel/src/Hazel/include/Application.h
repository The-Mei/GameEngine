#pragma once

#include "Core.h"

#include "Window.h"
#include "Layer/LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

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

        unsigned int mVao;
        std::unique_ptr<Shader> mShader;
        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<IndexBuffer> mIndexBuffer;

        static Application *gInstance;
    };

    // To be defined in client
    Application *createApplication();

}