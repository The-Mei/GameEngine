#include "Hazel.h"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "imgui.h"
#include "OpenGlShader.h"
class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example"), mCamera(-3.0, 3.0, -1.8, 1.8), mCameraPosition(0), mSquarePosition(0)
    {
        mVertexArray.reset(Hazel::VertexArray::create());

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

        mShader.reset(Hazel::Shader::create(vertexSrc, fragSrc));

        mSquareVA.reset(Hazel::VertexArray::create());

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

        mflatColorShader.reset(Hazel::Shader::create(flatColorvertexSrc, flatColorfragSrc));

        mTextureShader.reset(Hazel::Shader::create(std::string(RESROOT) + "/assets/shader/Texture.glsl"));
        mTexture2D = Hazel::Texture2D::create(std::string(RESROOT) + "/assets/textures/Checkerboard.png");

        mChernoLogo = Hazel::Texture2D::create(std::string(RESROOT) + "/assets/textures/ChernoLogo.png");

        std::dynamic_pointer_cast<Hazel::OpenGlShader>(mTextureShader)->bind();
        std::dynamic_pointer_cast<Hazel::OpenGlShader>(mTextureShader)->setUniform1i("sampler", 0);
    }

    void onUpdate(Hazel::Timestep ts) override
    {
        // LOGCT("Delta time: {0}s ({1}ms)", ts.getSeconds(), ts.getMilliseconds());

        if (Hazel::Input::isKeyPressed(HZ_KEY_LEFT))
            mCameraPosition.x -= mCameraMoveSpeed * ts;
        else if (Hazel::Input::isKeyPressed(HZ_KEY_RIGHT))
            mCameraPosition.x += mCameraMoveSpeed * ts;

        if (Hazel::Input::isKeyPressed(HZ_KEY_DOWN))
            mCameraPosition.y -= mCameraMoveSpeed * ts;
        else if (Hazel::Input::isKeyPressed(HZ_KEY_UP))
            mCameraPosition.y += mCameraMoveSpeed * ts;

        if (Hazel::Input::isKeyPressed(HZ_KEY_A))
            mCameraRotation += mCameraRotationSpeed * ts;
        else if (Hazel::Input::isKeyPressed(HZ_KEY_D))
            mCameraRotation -= mCameraRotationSpeed * ts;

        if (Hazel::Input::isKeyPressed(HZ_KEY_J))
            mSquarePosition.x -= mCameraMoveSpeed * ts;
        else if (Hazel::Input::isKeyPressed(HZ_KEY_L))
            mSquarePosition.x += mCameraMoveSpeed * ts;

        if (Hazel::Input::isKeyPressed(HZ_KEY_I))
            mSquarePosition.y += mCameraMoveSpeed * ts;
        else if (Hazel::Input::isKeyPressed(HZ_KEY_K))
            mSquarePosition.y -= mCameraMoveSpeed * ts;

        Hazel::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Hazel::RenderCommand::clear();

        mCamera.setPosition(mCameraPosition);
        mCamera.setRotation(mCameraRotation);

        Hazel::Renderer::beginScene(mCamera);

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
        Hazel::Renderer::submit(mTextureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        mChernoLogo->bind();
        Hazel::Renderer::submit(mTextureShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
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
    }

private:
    Hazel::Ref<Hazel::Shader> mShader;
    Hazel::Ref<Hazel::VertexArray> mVertexArray;

    Hazel::Ref<Hazel::Shader> mflatColorShader, mTextureShader;
    Hazel::Ref<Hazel::VertexArray> mSquareVA;

    Hazel::Ref<Hazel::Texture2D> mTexture2D, mChernoLogo;

    Hazel::OrthographicCamera mCamera;
    glm::vec3 mCameraPosition;
    float mCameraMoveSpeed = 4.0f;

    float mCameraRotation = 0.0f;
    float mCameraRotationSpeed = 180.0f;

    glm::vec3 mSquarePosition;
    glm::vec3 mSquareColor = {0.0f, 0.0f, 0.0f};
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        pushLayer(new ExampleLayer());
    }

    ~Sandbox() {}
};

Hazel::Application *Hazel::createApplication()
{
    return new Sandbox();
}
