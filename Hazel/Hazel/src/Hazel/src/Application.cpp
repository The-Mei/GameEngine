#include "Application.h"

#include "Gl/Gl.h"

#include "Events/ApplicationEvent.h"
#include "Input.h"

#include "OpenGlBuffer.h"
namespace Hazel
{
    Application *Application::gInstance = nullptr;

    static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::kFloat:
        case ShaderDataType::kFloat2:
        case ShaderDataType::kFloat3:
        case ShaderDataType::kFloat4:
        case ShaderDataType::kMat3:
        case ShaderDataType::kMat4:
            return GL_FLOAT;
        case ShaderDataType::kInt:
        case ShaderDataType::kInt2:
        case ShaderDataType::kInt3:
        case ShaderDataType::kInt4:
            return GL_INT;
        case ShaderDataType::kBool:
            return GL_BOOL;
        }
        HZ_CORE_ASSERT(false, "Unkown ShaderDataType!");
        return 0;
    }

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
            -0.5, -0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f,
            0.5, -0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f,
            0.0, 0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f};

        mVertexBuffer.reset(VertexBuffer::create(vertex, sizeof(vertex)));

        BufferLayout layout = {
            {ShaderDataType::kFloat3, "aPos"},
            {ShaderDataType::kFloat4, "aColor"}};

        uint32_t index = 0;
        for (auto &element : layout)
        {

            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.getComponentCount(),
                                  ShaderDataTypeToOpenGlBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(), (void *)(element.offset));
            index++;
        }

        uint32_t indices[] = {
            0, 1, 2};
        mIndexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(indices[0])));

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