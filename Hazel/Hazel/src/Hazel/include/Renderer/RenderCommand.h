#pragma once

#include "Renderer/RendererAPI.h"

namespace Hazel
{
    class HAZEL_API RenderCommand
    {
    public:
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