#pragma once

#include "Hazel.h"

class Sandbox2D : public Hazel::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;
    virtual void onUpdate(Hazel::Timestep ts) override;
    virtual void onImGuiRender() override;
    virtual void onEvent(Hazel::Event &event) override;

private:
    Hazel::OrthographicCameraController mCameraController;

    Hazel::Ref<Hazel::Shader> mflatColorShader;
    Hazel::Ref<Hazel::VertexArray> mSquareVA;

    glm::vec4 mSquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};