#pragma once

#include "Renderer/RendererAPI.h"

namespace Hazel
{
    class HAZEL_API RenderCommand
    {
    public:
        inline static void init()
        {
            sRendererAPI->init();
        }

        inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            sRendererAPI->setViewport(x, y, width, height);
        }

        inline static void setClearColor(const glm::vec4 &color)
        {
            sRendererAPI->setClearColor(color);
        }

        inline static void clear()
        {
            sRendererAPI->clear();
        }

        inline static void drawIndexed(const Ref<VertexArray> &vertexArray)
        {
            sRendererAPI->drawIndexed(vertexArray);
        }

    private:
        static RendererAPI *sRendererAPI;
    };

}