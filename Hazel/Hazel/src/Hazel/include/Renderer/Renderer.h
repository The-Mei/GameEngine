#pragma once

#include "Renderer/RenderCommand.h"

#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"
namespace Hazel
{
    class HAZEL_API Renderer
    {
    public:
        static void beginScene(OrthographicCamera &camera);
        static void endScene();

        static void submit(const Ref<Shader> &shader, const Ref<VertexArray> &vertexArray, glm::mat4 modelMatrix = glm::mat4(1.0f));

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 viewProjectMatrix;
        };

        static SceneData *mSceneData;
    };
}