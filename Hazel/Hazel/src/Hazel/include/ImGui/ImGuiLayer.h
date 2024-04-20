#pragma once

#include "Layer/Layer.h"

namespace Hazel
{
    class HAZEL_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onImGuiRender() override;

        void begin();
        void end();

        //     void onEvent(Event &event);
        //     void onUpdate();

        // private:
        //     bool onMouseButtonPressedEvent(MouseButtonPressedEvent &e);
        //     bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent &e);
        //     bool onMouseMovedEvent(MouseMovedEvent &e);
        //     bool onMouseScrolledEvent(MouseScrolledEvent &e);
        //     bool onKeyPressedEvent(KeyPressedEvent &e);
        //     bool onKeyReleasedEvent(KeyReleasedEvent &e);
        //     bool onKeyTypedEvent(KeyTypedEvent &e);
        //     bool onWindowResizedEvent(WindowResizeEvent &e);

    private:
        float mTime = 0.0f;
    };
}