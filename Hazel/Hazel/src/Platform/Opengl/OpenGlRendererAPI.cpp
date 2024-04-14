#include "Hzpch.h"

#include "OpenGlRendererAPI.h"

#include "glad/glad.h"

namespace Hazel
{
    void OpenGlRendererAPI::setClearColor(const glm::vec4 &color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGlRendererAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGlRendererAPI::drawIndexed(const std::shared_ptr<VertexArray> &vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
    }
}