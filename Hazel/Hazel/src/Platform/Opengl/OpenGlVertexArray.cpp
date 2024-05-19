
#include "OpenGlVertexArray.h"
#include "Hzpch.h"
#include "glad/glad.h"
#include "GlCheckError.h"

namespace Hazel
{

    static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::kFloat:
        case ShaderDataType::kFloat2:
        case ShaderDataType::kFloat3:
        case ShaderDataType::kFloat4:
        case ShaderDataType::kMat3:
        case ShaderDataType::kMat4:
            return GL_FLOAT;
        case ShaderDataType::kInt:
        case ShaderDataType::kInt2:
        case ShaderDataType::kInt3:
        case ShaderDataType::kInt4:
            return GL_INT;
        case ShaderDataType::kBool:
            return GL_BOOL;
        }
        HZ_CORE_ASSERT(false, "Unkown ShaderDataType!");
        return 0;
    }

    OpenGlVertexArray::OpenGlVertexArray()
    {
        GLCHECK(glCreateVertexArrays(1, &mRendererId));
    }

    OpenGlVertexArray::~OpenGlVertexArray()
    {
        glDeleteVertexArrays(1, &mRendererId);
    }

    void OpenGlVertexArray::bind() const
    {
        GLCHECK(glBindVertexArray(mRendererId));
    }

    void OpenGlVertexArray::unBind() const
    {
        GLCHECK(glBindVertexArray(0));
    }

    void OpenGlVertexArray::addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer)
    {
        HZ_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer is no layout!");

        GLCHECK(glBindVertexArray(mRendererId));
        vertexBuffer->bind();

        uint32_t index = 0;
        const auto &layout = vertexBuffer->getLayout();
        for (auto &element : layout)
        {

            GLCHECK(glEnableVertexAttribArray(index));
            GLCHECK(glVertexAttribPointer(index,
                                          element.getComponentCount(),
                                          ShaderDataTypeToOpenGlBaseType(element.type),
                                          element.normalized ? GL_TRUE : GL_FALSE,
                                          layout.getStride(),
                                          (void *)element.offset));
            index++;
        }

        mVertexBuffer.push_back(vertexBuffer);
    }

    void OpenGlVertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
    {
        GLCHECK(glBindVertexArray(mRendererId));
        indexBuffer->bind();

        mIndexBuffer = indexBuffer;
    }
}