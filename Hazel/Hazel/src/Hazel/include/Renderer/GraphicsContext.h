#pragma once

namespace Hazel
{
    class HAZEL_API GraphicsContext
    {
    public:
        virtual ~GraphicsContext() {}
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };

}