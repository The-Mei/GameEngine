#pragma once

#include "Events/Event.h"

// #include <sstream>

namespace Hazel
{
    class HAZEL_API WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : mWidth(width), mHeight(height) {}

        inline unsigned int getWidth() const { return mWidth; }
        inline unsigned int getHeight() const { return mHeight; }

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << mWidth << ", " << mHeight;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kWindowResize)
        EVENT_CLASS_CATEGORY(kEventCategoryApplication)

    private:
        unsigned int mWidth, mHeight;
    };

    class HAZEL_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(kWindowClose)
        EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    };

    class HAZEL_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(kAppTick)
        EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    };

    class HAZEL_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(kAppUpdate)
        EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    };

    class HAZEL_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(kAppRender)
        EVENT_CLASS_CATEGORY(kEventCategoryApplication)
    };
}