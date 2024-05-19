#pragma once

#include "Core/Input.h"

namespace Hazel
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool isKeyPressedImpl(int keyCode) override;

        virtual bool isMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> getMousePositionImpl() override;
        virtual float getMouseXImpl() override;
        virtual float getMouseYImpl() override;
    };

}