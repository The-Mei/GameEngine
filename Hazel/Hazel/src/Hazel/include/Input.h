#pragma once

namespace Hazel
{
    class HAZEL_API Input
    {
    public:
        inline static bool isKeyPressed(int keyCode) { return gInstance->isKeyPressedImpl(keyCode); }

        inline static bool isMouseButtonPressed(int button) { return gInstance->isMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> getMousePosition() { return gInstance->getMousePositionImpl(); }
        inline static float getMouseX() { return gInstance->getMouseXImpl(); }
        inline static float getMouseY() { return gInstance->getMouseYImpl(); }

    protected:
        virtual bool isKeyPressedImpl(int keyCode) = 0;
        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> getMousePositionImpl() = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;

    private:
        static Input *gInstance;
    };

}