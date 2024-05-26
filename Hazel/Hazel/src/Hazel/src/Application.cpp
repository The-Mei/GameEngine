#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Core/Input.h"

#include "glfw/glfw3.h"

#include "Renderer/Renderer.h"
#include "Renderer/Renderer2D.h"

namespace Hazel
{
    Application *Application::gInstance = nullptr;

    Application::Application() : mRunning(false), mMinimized(false)
    {
        gInstance = this;
        mWindow = std::unique_ptr<Window>(Window::create());
        mWindow->setEventCallback(HZ_BIND_EVENT_FN(onEvent));

        Renderer::init();
        Renderer2D::init();

        mImGuiLayer = new ImGuiLayer();
        pushOverlay(mImGuiLayer);
        mRunning = true;
    }

    Application::~Application() {}

    void Application::onEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(onWindowResize));

        for (auto it = mLayerStack.end(); it != mLayerStack.begin();)
        {
            (*--it)->onEvent(e);
            if (e.mHandled)
                break;
        }
    }

    void Application::pushLayer(Layer *layer)
    {
        mLayerStack.pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer *overlay)
    {
        mLayerStack.pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::run()
    {
        while (mRunning)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - mLastFrameTime;
            mLastFrameTime = time;

            if (!mMinimized)
            {
                for (Layer *layer : mLayerStack)
                    layer->onUpdate(timestep);
            }

            mImGuiLayer->begin();
            for (Layer *layer : mLayerStack)
                layer->onImGuiRender();
            mImGuiLayer->end();
            mWindow->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent &e)
    {
        mRunning = false;
        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent &e)
    {
        if (e.getWidth() == 0 || e.getHeight() == 0)
        {
            mMinimized = true;
            return false;
        }
        mMinimized = false;
        Renderer::onWindowResize(e.getWidth(), e.getHeight());
        return false;
    }
}