#include "Sandbox2D.h"

#include "imgui.h"
#include "OpenGlShader.h"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D"), mCameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::onAttach()
{
    mSquareVA = Hazel::VertexArray::create();

    float squareVertices[] = {
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0};

    Hazel::Ref<Hazel::VertexBuffer> squareVB;
    squareVB.reset(Hazel::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

    Hazel::BufferLayout flatColorlayout = {
        {Hazel::ShaderDataType::kFloat3, "aPos"}};

    squareVB->setLayout(flatColorlayout);

    mSquareVA->addVertexBuffer(squareVB);

    uint32_t flatColorindices[] = {
        0, 1, 2,
        2, 3, 0};
    Hazel::Ref<Hazel::IndexBuffer> squareIB;
    squareIB.reset(Hazel::IndexBuffer::create(flatColorindices, sizeof(flatColorindices) / sizeof(flatColorindices[0])));

    mSquareVA->setIndexBuffer(squareIB);

    mflatColorShader = Hazel::Shader::create(std::string(RESROOT) + "/assets/shader/FlatColor.glsl");
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate(Hazel::Timestep ts)
{
    mCameraController.onUpdate(ts);

    Hazel::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Hazel::RenderCommand::clear();

    Hazel::Renderer::beginScene(mCameraController.getCamera());

    std::dynamic_pointer_cast<Hazel::OpenGlShader>(mflatColorShader)->bind();
    std::dynamic_pointer_cast<Hazel::OpenGlShader>(mflatColorShader)->setUniform4f("u_color", mSquareColor);

    Hazel::Renderer::submit(mflatColorShader, mSquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Hazel::Renderer::endScene();
}

void Sandbox2D::onImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(mSquareColor));
    ImGui::End();
}

void Sandbox2D::onEvent(Hazel::Event &event)
{
    mCameraController.onEvent(event);
}