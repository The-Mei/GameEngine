#pragma once

#include "Camera/OrthographicCamera.h"
#include "Renderer/Texture.h"

namespace Hazel
{
    class HAZEL_API Renderer2D
    {
    public:
        static void init();
        static void shutDown();

        static void beginScene(OrthographicCamera &camera);
        static void endScene();

        static void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
        static void drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);

        static void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture);
        static void drawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture);
    };
}