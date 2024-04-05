#include "Application.h"

#include "Gl/Gl.h"

#include "Events/ApplicationEvent.h"
#include "Input.h"

#include "OpenGlBuffer.h"
namespace Hazel
{
    Application *Application::gInstance = nullptr;

    Application::Application() : mRunning(false)
    {
        gInstance = this;
        mWindow = std::unique_ptr<Window>(Window::create());
        mWindow->setEventCallback(HZ_BIND_EVENT_FN(onEvent));
        mImGuiLayer = new ImGuiLayer();
        pushOverlay(mImGuiLayer);
        mRunning = true;

        glGenVertexArrays(1, &mVao);
        glBindVertexArray(mVao);

        float vertex[] = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.0, 0.5, 0.0};

        mVertexBuffer.reset(VertexBuffer::create(vertex, sizeof(vertex)));
        mVertexBuffer->bind();

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

        uint32_t indices[] = {
            0, 1, 2};
        mIndexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(indices[0])));
        mIndexBuffer->bind();

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            void main()
            {
                gl_position = vec4(aPos, 1.0);
            }
        )";

        std::string fragSrc = R"(
            #version 330 core
            out vec4 color;
            void main()
            {
                color = vec4(1.0, 0.0, 0.0, 1.0);
            }
        )";

        mShader.reset(new Shader(vertexSrc, fragSrc));
    }

    Application::~Application() {}

    void Application::onEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(HZ_BIND_EVENT_FN(onWindowClose));

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
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            mShader->bind();
            glBindVertexArray(mVao);
            glDrawElements(GL_TRIANGLES, mIndexBuffer->getCount(), GL_UNSIGNED_INT, 0);

            for (Layer *layer : mLayerStack)
                layer->onUpdate();

            mImGuiLayer->begin();
            for (Layer *layer : mLayerStack)
                layer->onImGuiRender();
            mImGuiLayer->end();
            mWindow->onUpdate();
        }
    }

    bool Application::onWindowClose(class WindowCloseEvent &e)
    {
        mRunning = false;
        return true;
    }
}