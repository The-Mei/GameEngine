#include "Hzpch.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Renderer.h"

#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

#include "gtc/matrix_transform.hpp"

namespace Hazel
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> quadVA;
        Ref<Shader> flatColorShader;
        Ref<Shader> textureShader;
    };

    static Renderer2DStorage *sData;

    void Renderer2D::init()
    {
        sData = new Renderer2DStorage();

        sData->quadVA = VertexArray::create();

        float squareVertices[] = {
            -0.5, -0.5, 0.0, 0.0f, 0.0f,
            0.5, -0.5, 0.0, 1.0f, 0.0f,
            0.5, 0.5, 0.0, 1.0f, 1.0f,
            -0.5, 0.5, 0.0, 0.0f, 1.0f};

        Ref<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        BufferLayout flatColorlayout = {
            {ShaderDataType::kFloat3, "aPos"},
            {ShaderDataType::kFloat2, "aTexCoord"}};

        squareVB->setLayout(flatColorlayout);

        sData->quadVA->addVertexBuffer(squareVB);

        uint32_t flatColorindices[] = {
            0, 1, 2,
            2, 3, 0};
        Ref<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::create(flatColorindices, sizeof(flatColorindices) / sizeof(flatColorindices[0])));

        sData->quadVA->setIndexBuffer(squareIB);

        sData->flatColorShader = Shader::create(std::string(RESROOT) + "/assets/shader/FlatColor.glsl");
        sData->textureShader = Shader::create(std::string(RESROOT) + "/assets/shader/Texture.glsl");
        sData->textureShader->bind();
        sData->textureShader->setInt("sampler", 0);
    }

    void Renderer2D::shutDown()
    {
        delete sData;
    }

    void Renderer2D::beginScene(OrthographicCamera &camera)
    {
        sData->flatColorShader->bind();
        sData->flatColorShader->setMat4("u_ViewProject", camera.getViewProjectMatrix());

        sData->textureShader->bind();
        sData->textureShader->setMat4("u_ViewProject", camera.getViewProjectMatrix());
    }

    void Renderer2D::endScene()
    {
        Renderer::endScene();
    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        drawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
    {
        sData->flatColorShader->bind();
        sData->flatColorShader->setFloat4("u_color", color);

        glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        sData->flatColorShader->setMat4("u_Model", transfrom);

        sData->quadVA->bind();
        RenderCommand::drawIndexed(sData->quadVA);
    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture2D> &texture)
    {
        drawQuad({position.x, position.y, 0.0f}, size, texture);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture2D> &texture)
    {
        sData->textureShader->bind();

        glm::mat4 transfrom = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        sData->textureShader->setMat4("u_Model", transfrom);

        texture->bind();

        sData->quadVA->bind();
        RenderCommand::drawIndexed(sData->quadVA);
    }
}
