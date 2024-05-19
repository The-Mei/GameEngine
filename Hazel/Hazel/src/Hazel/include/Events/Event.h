#pragma once

#include "Core/Core.h"

// #include <string>
// #include <functional>

namespace Hazel
{
    enum class EventType
    {
        kNone = 0,
        kWindowClose,
        kWindowResize,
        kWindowFocus,
        kWindowLostFocus,
        kWindowMoved,
        kAppTick,
        kAppUpdate,
        kAppRender,
        kKeyPressed,
        kKeyReleased,
        kKeyTyped,
        kMouseButtonPressed,
        kMouseButtonReleased,
        kMouseMoved,
        kMouseScrolled,
    };

    enum EventCategory
    {
        kNone = 0,
        kEventCategoryApplication = BIT(0),
        kEventCategoryInput = BIT(1),
        kEventCategoryKeyboard = BIT(2),
        kEventCategoryMouse = BIT(3),
        kEventCategoryMouseButton = BIT(4),

    };

#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType getStaticType() { return EventType::type; }                \
    virtual EventType getEventType() const override { return getStaticType(); } \
    virtual const char *getName() const override                                \
    {                                                                           \
        return #type;                                                           \
    }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int getCategoryFlags() const override { return category; }

    class HAZEL_API Event
    {
        friend class EventDispatcher;

    public:
        virtual EventType getEventType() const = 0;
        virtual const char *getName() const = 0;
        virtual int getCategoryFlags() const = 0;
        virtual std::string toString() const { return getName(); }

        inline bool isInCategory(EventCategory category)
        {
            return getCategoryFlags() & category;
        }

    public:
        bool mHandled = false;
    };

    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T &)>;

    public:
        EventDispatcher(Event &event)
            : mEvent(event) {}

        template <typename T>
        bool dispatch(EventFn<T> func)
        {
            if (mEvent.getEventType() == T::getStaticType())
            {
                mEvent.mHandled = func(*(T *)&mEvent);
                return true;
            }
            return false;
        }

    private:
        Event &mEvent;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e)
    {
        return os << e.toString();
    }
}