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
    mCheckerboardTexture = Hazel::Texture2D::create(std::string(RESROOT) + "/assets/textures/Checkerboard.png");
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate(Hazel::Timestep ts)
{
    mCameraController.onUpdate(ts);

    Hazel::RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Hazel::RenderCommand::clear();

    Hazel::Renderer2D::beginScene(mCameraController.getCamera());

    Hazel::Renderer2D::drawQuad({-0.5f, 0.0f}, {0.5f, 0.5f}, {0.8f, 0.2f, 0.3f, 1.0f});
    Hazel::Renderer2D::drawQuad({0.5f, -0.5f}, {0.8f, 0.9f}, {0.3f, 0.2f, 0.8f, 1.0f});
    Hazel::Renderer2D::drawQuad({0.5f, 0.5f, -0.1f}, {10.0f, 10.0f}, mCheckerboardTexture);

    Hazel::Renderer2D::endScene();
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