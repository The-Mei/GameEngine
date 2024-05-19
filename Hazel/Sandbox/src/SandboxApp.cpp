#include "Hazel.h"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "imgui.h"
#include "OpenGlShader.h"

#include "Sandbox2D.h"

#include "Core/EntryPoint.h"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example"), mCameraController(1280.0f / 720.0f)
    {
        mVertexArray = Hazel::VertexArray::create();

        float vertex[] = {
            -0.5, -0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f,
            0.5, -0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f,
            0.0, 0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f};

        Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Hazel::VertexBuffer::create(vertex, sizeof(vertex)));

        Hazel::BufferLayout layout = {
            {Hazel::ShaderDataType::kFloat3, "aPos"},
            {Hazel::ShaderDataType::kFloat4, "aColor"}};

        vertexBuffer->setLayout(layout);

        mVertexArray->addVertexBuffer(vertexBuffer);

        uint32_t indices[] = {
            0, 1, 2};
        Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
        indexBuffer.reset(Hazel::IndexBuffer::create(indices, sizeof(indices) / sizeof(indices[0])));

        mVertexArray->setIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec4 aColor;
            uniform mat4 u_ViewProject;
            uniform mat4 u_Model;
            out vec4 vColor;
            void main()
            {
                gl_Position = u_ViewProject * u_Model * vec4(aPos, 1.0);
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

        mShader = Hazel::Shader::create("vertexPosition", vertexSrc, fragSrc);

        mSquareVA = Hazel::VertexArray::create();

        float squareVertices[] = {
            -0.5, -0.5, 0.0, 0.0f, 0.0f,
            0.5, -0.5, 0.0, 1.0f, 0.0,
            0.5, 0.5, 0.0, 1.0f, 1.0f,
            -0.5, 0.5, 0.0, 0.0f, 1.0f};

        Hazel::Ref<Hazel::VertexBuffer> squareVB;
        squareVB.reset(Hazel::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        Hazel::BufferLayout flatColorlayout = {
            {Hazel::ShaderDataType::kFloat3, "aPos"},
            {Hazel::ShaderDataType::kFloat2, "aTexCoord"}};

        squareVB->setLayout(flatColorlayout);

        mSquareVA->addVertexBuffer(squareVB);

        uint32_t flatColorindices[] = {
            0, 1, 2,
            2, 3, 0};
        Hazel::Ref<Hazel::IndexBuffer> squareIB;
        squareIB.reset(Hazel::IndexBuffer::create(flatColorindices, sizeof(flatColorindices) / sizeof(flatColorindices[0])));

        mSquareVA->setIndexBuffer(squareIB);

        std::string flatColorvertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            uniform mat4 u_ViewProject;
            uniform mat4 u_Model;
            void main()
            {
                gl_Position = u_ViewProject * u_Model * vec4(aPos , 1.0);
            }
        )";

        std::string flatColorfragSrc = R"(
            #version 330 core
            uniform vec3 u_color;
            out vec4 color;
            void main()
            {
                color = vec4(u_color, 1.0);
            }
        )";

        mflatColorShader = Hazel::Shader::create("flatColor", flatColorvertexSrc, flatColorfragSrc);

        auto textureShader = mShaderLibrary.load(std::string(RESROOT) + "/assets/shader/Texture.glsl");
        mTexture2D = Hazel::Texture2D::create(std::string(RESROOT) + "/assets/textures/Checkerboard.png");

        mChernoLogo = Hazel::Texture2D::create(std::string(RESROOT) + "/assets/textures/ChernoLogo.png");

        std::dynamic_pointer_cast<Hazel::OpenGlShader>(textureShader)->bind();
        std::dynamic_pointer_cast<Hazel::OpenGlShader>(textureShader)->setUniform1i("sampler", 0);
    }

    void onUpdate(Hazel::Timestep ts) override
    {
        // LOGCT("Delta time: {0}s ({1}ms)", ts.getSeconds(), ts.getMilliseconds());
        mCameraController.onUpdate(ts);

        Hazel::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Hazel::RenderCommand::clear();

        Hazel::Renderer::beginScene(mCameraController.getCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Hazel::OpenGlShader>(mflatColorShader)->bind();
        std::dynamic_pointer_cast<Hazel::OpenGlShader>(mflatColorShader)->setUniform3f("u_color", mSquareColor);
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.11f, y * 0.11f, 0.0f)) * scale;
                Hazel::Renderer::submit(mflatColorShader, mSquareVA, transform);
            }
        }
        mTexture2D->bind();
        auto textureShader = mShaderLibrary.get("Texture");
        Hazel::Renderer::submit(textureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        mChernoLogo->bind();
        Hazel::Renderer::submit(textureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        // Hazel::Renderer::submit(mShader, mVertexArray);

        Hazel::Renderer::endScene();
    }

    virtual void onImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(mSquareColor));
        ImGui::End();
    }

    void onEvent(Hazel::Event &event) override
    {
        mCameraController.onEvent(event);
    }

private:
    Hazel::ShaderLibrary mShaderLibrary;
    Hazel::Ref<Hazel::Shader> mShader;
    Hazel::Ref<Hazel::VertexArray> mVertexArray;

    Hazel::Ref<Hazel::Shader> mflatColorShader;
    Hazel::Ref<Hazel::VertexArray> mSquareVA;

    Hazel::Ref<Hazel::Texture2D> mTexture2D, mChernoLogo;

    Hazel::OrthographicCameraController mCameraController;

    glm::vec3 mSquareColor = {0.0f, 0.0f, 0.0f};
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        // pushLayer(new ExampleLayer());
        pushLayer(new Sandbox2D());
    }

    ~Sandbox() {}
};

Hazel::Application *Hazel::createApplication()
{
    return new Sandbox();
}
