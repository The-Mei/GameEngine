#pragma once

#include "Events/Event.h"

// #include <sstream>

namespace Hazel
{
    class HAZEL_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : mMouseX(x), mMouseY(y) {}

        inline float getX() const { return mMouseX; }
        inline float getY() const { return mMouseY; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << mMouseX << ", " << mMouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kMouseMoved)
        EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)

    private:
        float mMouseX, mMouseY;
    };

    class HAZEL_API MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : mXOffset(xOffset), mYOffset(yOffset) {}

        inline float getXOffset() const { return mXOffset; }
        inline float getYOffset() const { return mYOffset; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << mXOffset << ", " << mYOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kMouseScrolled)
        EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)

    private:
        float mXOffset, mYOffset;
    };

    class HAZEL_API MouseButtonEvent : public Event
    {
    public:
        inline int getMouseButton() const { return mButton; }

        EVENT_CLASS_CATEGORY(kEventCategoryMouse | kEventCategoryInput)

    protected:
        MouseButtonEvent(int button)
            : mButton(button) {}

        int mButton;
    };

    class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << mButton;
            return ss.str();
        }
        EVENT_CLASS_TYPE(kMouseButtonPressed)
    };

    class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << mButton;
            return ss.str();
        }
        EVENT_CLASS_TYPE(kMouseButtonReleased)
    };
}