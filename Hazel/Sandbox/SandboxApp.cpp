#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example"), mCamera(-1.0, 1.0, -1.0, 1.0), mCameraPosition(0)
    {
        mVertexArray.reset(Hazel::VertexArray::create());

        float vertex[] = {
            -0.5, -0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f,
            0.5, -0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f,
            0.0, 0.5, 0.0, 1.0f, 0.0f, 0.5f, 1.0f};

        std::shared_ptr<Hazel::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Hazel::VertexBuffer::create(vertex, sizeof(vertex)));

        Hazel::BufferLayout layout = {
            {Hazel::ShaderDataType::kFloat3, "aPos"},
            {Hazel::ShaderDataType::kFloat4, "aColor"}};

        vertexBuffer->setLayout(layout);

        mVertexArray->addVertexBuffer(vertexBuffer);

        uint32_t indices[] = {
            0, 1, 2};
        std::shared_ptr<Hazel::IndexBuffer> indexBuffer;
        indexBuffer.reset(Hazel::IndexBuffer::create(indices, sizeof(indices) / sizeof(indices[0])));

        mVertexArray->setIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec4 aColor;
            uniform mat4 u_ViewProject;
            out vec4 vColor;
            void main()
            {
                gl_Position = u_ViewProject * vec4(aPos, 1.0);
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

        mShader.reset(new Hazel::Shader(vertexSrc, fragSrc));

        mSquareVA.reset(Hazel::VertexArray::create());

        float bluevertex[] = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.5, 0.5, 0.0,
            -0.5, 0.5, 0.0};

        std::shared_ptr<Hazel::VertexBuffer> squareVB;
        squareVB.reset(Hazel::VertexBuffer::create(bluevertex, sizeof(bluevertex)));

        Hazel::BufferLayout bluelayout = {
            {Hazel::ShaderDataType::kFloat3, "aPos"}};

        squareVB->setLayout(bluelayout);

        mSquareVA->addVertexBuffer(squareVB);

        uint32_t blueindices[] = {
            0, 1, 2,
            2, 3, 0};
        std::shared_ptr<Hazel::IndexBuffer> squareIB;
        squareIB.reset(Hazel::IndexBuffer::create(blueindices, sizeof(blueindices) / sizeof(blueindices[0])));

        mSquareVA->setIndexBuffer(squareIB);

        std::string bluevertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            uniform mat4 u_ViewProject;
            void main()
            {
                gl_Position = u_ViewProject * vec4(aPos , 1.0);
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

        mBlueShader.reset(new Hazel::Shader(bluevertexSrc, bluefragSrc));
    }

    void onUpdate() override
    {

        if (Hazel::Input::isKeyPressed(HZ_KEY_LEFT))
            mCameraPosition.x -= mCameraMoveSpeed;
        else if (Hazel::Input::isKeyPressed(HZ_KEY_RIGHT))
            mCameraPosition.x += mCameraMoveSpeed;

        if (Hazel::Input::isKeyPressed(HZ_KEY_DOWN))
            mCameraPosition.y -= mCameraMoveSpeed;
        else if (Hazel::Input::isKeyPressed(HZ_KEY_UP))
            mCameraPosition.y += mCameraMoveSpeed;

        if (Hazel::Input::isKeyPressed(HZ_KEY_A))
            mCameraRotation += mCameraRotationSpeed;
        else if (Hazel::Input::isKeyPressed(HZ_KEY_D))
            mCameraRotation -= mCameraRotationSpeed;

        Hazel::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Hazel::RenderCommand::clear();

        mCamera.setPosition(mCameraPosition);
        mCamera.setRotation(mCameraRotation);

        Hazel::Renderer::beginScene(mCamera);

        Hazel::Renderer::submit(mBlueShader, mSquareVA);
        Hazel::Renderer::submit(mShader, mVertexArray);

        Hazel::Renderer::endScene();
    }

    void onEvent(Hazel::Event &event) override
    {
    }

private:
    std::shared_ptr<Hazel::Shader> mShader;
    std::shared_ptr<Hazel::VertexArray> mVertexArray;

    std::shared_ptr<Hazel::Shader> mBlueShader;
    std::shared_ptr<Hazel::VertexArray> mSquareVA;

    Hazel::OrthographicCamera mCamera;
    glm::vec3 mCameraPosition;
    float mCameraMoveSpeed = 0.1f;

    float mCameraRotation = 0.0f;
    float mCameraRotationSpeed = 2.1f;
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
