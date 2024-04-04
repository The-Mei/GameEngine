#pragma once

namespace Hazel
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() {}
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };

}