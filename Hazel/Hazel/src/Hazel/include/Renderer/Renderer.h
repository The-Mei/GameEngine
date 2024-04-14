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

        static void submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray);

        inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 viewProjectMatrix;
        };

        static SceneData *mSceneData;
    };
}