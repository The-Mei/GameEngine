#pragma once

namespace Hazel
{
    enum class RendererAPI
    {
        kNone = 0,
        kOpenGl = 1
    };

    class Renderer
    {
    public:
        inline static RendererAPI getAPI() { return sRendererAPI; }

    private:
        static RendererAPI sRendererAPI;
    };
}