#pragma once

#include "Events/Event.h"

#include <sstream>

namespace Hazel
{
    class HAZEL_API KeyEvent : public Event
    {
    public:
        inline int getKeyCode() const { return mKeyCode; }
        EVENT_CLASS_CATEGORY(kEventCategoryKeyboard | kEventCategoryInput)
    protected:
        KeyEvent(int keyCode)
            : mKeyCode(keyCode) {}

        int mKeyCode;
    };

    class HAZEL_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), mRepeatCount(repeatCount) {}

        inline int getRepeatCount() const { return mRepeatCount; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << mKeyCode << " (" << mRepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(kKeyPressed)
    private:
        int mRepeatCount;
    };

    class HAZEL_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keyCode)
            : KeyEvent(keyCode) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << mKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kKeyReleased)
    };

    class HAZEL_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keyCode)
            : KeyEvent(keyCode) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << mKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kKeyTyped)
    };
}
