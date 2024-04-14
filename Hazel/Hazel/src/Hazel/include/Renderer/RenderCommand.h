#pragma once

#include "Renderer/RendererAPI.h"

namespace Hazel
{
    class RenderCommand
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

        inline static void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
        {
            sRendererAPI->drawIndexed(vertexArray);
        }

    private:
        static RendererAPI *sRendererAPI;
    };

}