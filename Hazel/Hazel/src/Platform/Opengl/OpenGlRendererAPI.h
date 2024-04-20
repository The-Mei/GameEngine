#pragma once

#include "Renderer/RendererAPI.h"

namespace Hazel
{
    class OpenGlRendererAPI : public RendererAPI
    {
    public:
        virtual void setClearColor(const glm::vec4 &color) override;
        virtual void clear() override;

        virtual void drawIndexed(const Ref<VertexArray> &vertexArray) override;
    };

}