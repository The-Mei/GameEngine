#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example") {}

    void onUpdate() override
    {
        // LOGCI("ExampleLayer::update");
    }

    void onEvent(Hazel::Event &event) override
    {
        // LOGCT("{0}", event);
    }
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        pushLayer(new ExampleLayer());
        pushOverlay(new Hazel::ImGuiLayer());
    }

    ~Sandbox() {}
};

Hazel::Application *Hazel::createApplication()
{
    return new Sandbox();
}
