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

        mVertexArray.reset(VertexArray::create());

        float vertex[] = {
            -0.5, -0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f,
            0.5, -0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f,
            0.0, 0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f};

        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::create(vertex, sizeof(vertex)));

        BufferLayout layout = {
            {ShaderDataType::kFloat3, "aPos"},
            {ShaderDataType::kFloat4, "aColor"}};

        vertexBuffer->setLayout(layout);

        mVertexArray->addVertexBuffer(vertexBuffer);

        uint32_t indices[] = {
            0, 1, 2};
        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(indices[0])));

        mVertexArray->setIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec4 aColor;

            out vec4 vColor;
            void main()
            {
                gl_Position = vec4(aPos, 1.0);
                vColor = aColor;
            }
        )";

        std::string fragSrc = R"(
            #version 330 core
            in vec4 vColor;
            out vec4 color;
            void main()
            {
                color = vColor;
            }
        )";

        mShader.reset(new Shader(vertexSrc, fragSrc));

        mSquareVA.reset(VertexArray::create());

        float bluevertex[] = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.5, 0.5, 0.0,
            -0.5, 0.5, 0.0};

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::create(bluevertex, sizeof(bluevertex)));

        BufferLayout bluelayout = {
            {ShaderDataType::kFloat3, "aPos"}};

        squareVB->setLayout(bluelayout);

        mSquareVA->addVertexBuffer(squareVB);

        uint32_t blueindices[] = {
            0, 1, 2,
            2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::create(blueindices, sizeof(blueindices) / sizeof(blueindices[0])));

        mSquareVA->setIndexBuffer(squareIB);

        std::string bluevertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;

            void main()
            {
                gl_Position = vec4(aPos * 0.5 + 0.5, 1.0);
            }
        )";

        std::string bluefragSrc = R"(
            #version 330 core
            out vec4 color;
            void main()
            {
                color = vec4(0.2, 0.3, 0.2, 1.0);
            }
        )";

        mBlueShader.reset(new Shader(bluevertexSrc, bluefragSrc));
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
            mVertexArray->bind();
            glDrawElements(GL_TRIANGLES, mVertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);

            mBlueShader->bind();
            mSquareVA->bind();
            glDrawElements(GL_TRIANGLES, mSquareVA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);

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