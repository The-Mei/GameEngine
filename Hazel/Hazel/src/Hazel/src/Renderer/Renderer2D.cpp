#include "Hzpch.h"
#include "Renderer/Renderer2D.h"
#include "Renderer/Renderer.h"

#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "OpenGlShader.h"

namespace Hazel
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> quadVA;
        Ref<Shader> flatColorShader;
    };

    static Renderer2DStorage *sData;

    void Renderer2D::init()
    {
        sData = new Renderer2DStorage();

        sData->quadVA = VertexArray::create();

        float squareVertices[] = {
            -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0,
            0.5, 0.5, 0.0,
            -0.5, 0.5, 0.0};

        Ref<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));

        BufferLayout flatColorlayout = {
            {ShaderDataType::kFloat3, "aPos"}};

        squareVB->setLayout(flatColorlayout);

        sData->quadVA->addVertexBuffer(squareVB);

        uint32_t flatColorindices[] = {
            0, 1, 2,
            2, 3, 0};
        Ref<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::create(flatColorindices, sizeof(flatColorindices) / sizeof(flatColorindices[0])));

        sData->quadVA->setIndexBuffer(squareIB);

        sData->flatColorShader = Shader::create(std::string(RESROOT) + "/assets/shader/FlatColor.glsl");
    }

    void Renderer2D::shutDown()
    {
        delete sData;
    }

    void Renderer2D::beginScene(OrthographicCamera &camera)
    {
        std::dynamic_pointer_cast<OpenGlShader>(sData->flatColorShader)->bind();
        std::dynamic_pointer_cast<OpenGlShader>(sData->flatColorShader)->setUniformMatrix4fv("u_ViewProject", camera.getViewProjectMatrix());
        std::dynamic_pointer_cast<OpenGlShader>(sData->flatColorShader)->setUniformMatrix4fv("u_Model", glm::mat4(1.0f));
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
        std::dynamic_pointer_cast<OpenGlShader>(sData->flatColorShader)->bind();
        std::dynamic_pointer_cast<OpenGlShader>(sData->flatColorShader)->setUniform4f("u_color", color);

        sData->quadVA->bind();
        RenderCommand::drawIndexed(sData->quadVA);
    }
}
