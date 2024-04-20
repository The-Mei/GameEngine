#include "Hzpch.h"

#include "Renderer/Renderer.h"

#include "OpenGlShader.h"
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

    void Renderer::submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, glm::mat4 modelMatrix)
    {
        std::dynamic_pointer_cast<OpenGlShader>(shader)->bind();
        std::dynamic_pointer_cast<OpenGlShader>(shader)->setUniformMatrix4fv("u_ViewProject", mSceneData->viewProjectMatrix);
        std::dynamic_pointer_cast<OpenGlShader>(shader)->setUniformMatrix4fv("u_Model", modelMatrix);
        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }
}