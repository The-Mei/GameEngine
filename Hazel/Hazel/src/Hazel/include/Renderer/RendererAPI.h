#pragma once

#include "glm.hpp"
#include "Renderer/VertexArray.h"

namespace Hazel
{
    class RendererAPI
    {
    public:
        enum class API
        {
            kNone = 0,
            kOpenGl = 1
        };

    public:
        virtual void setClearColor(const glm::vec4 &color) = 0;
        virtual void clear() = 0;

        virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;

        inline static API getAPI() { return sAPI; }

    private:
        static API sAPI;
    };

}