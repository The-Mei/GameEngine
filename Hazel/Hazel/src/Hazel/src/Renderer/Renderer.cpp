#include "Hzpch.h"

#include "Renderer/Renderer.h"

#include "gtc/type_ptr.hpp"
namespace Hazel
{
    Renderer::SceneData *Renderer::mSceneData = new Renderer::SceneData;

    void Renderer::beginScene(OrthographicCamera &camera)
    {
        mSceneData->viewProjectMatrix = camera.getViewProjectMatrix();
    }

    void Renderer::endScene()
    {
    }

    void Renderer::submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray)
    {
        shader->bind();
        shader->setUniformMatrix4fv("u_ViewProject", glm::value_ptr(mSceneData->viewProjectMatrix));
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}