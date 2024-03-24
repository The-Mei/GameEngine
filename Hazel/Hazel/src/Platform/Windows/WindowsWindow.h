#pragma once

#include "Window.h"

struct GLFWwindow;

namespace Hazel
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps &props);
        virtual ~WindowsWindow();

        void onUpdate() override;

        inline unsigned int getWidth() const override { return mData.width; }
        inline unsigned int getHeight() const override { return mData.height; }

        inline void setEventCallback(const EventCallbackFn &callback) override { mData.eventCallback = callback; }
        void setVSync(bool enabled) override;
        bool isVSync() const override;

    private:
        virtual void init(const WindowProps &props);
        virtual void shutdown();

    private:
        GLFWwindow *mWindow;

        struct WindowData
        {
            std::string title;
            unsigned int width, height;
            bool vsync;

            EventCallbackFn eventCallback;
        };

        WindowData mData;
    };
}