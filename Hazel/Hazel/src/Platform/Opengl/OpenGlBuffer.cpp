#include "OpenGlBuffer.h"

#include "Hzpch.h"

#include "glad/glad.h"
#include "GlCheckError.h"

namespace Hazel
{
    OpenGlVertexBuffer::OpenGlVertexBuffer(float *vertices, uint32_t size)
    {
        GLCHECK(glCreateBuffers(1, &mRendererId));
        // glCreateBuffers取代下面
        // glGenBuffers(1, &mRendererId);

        GLCHECK(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
        GLCHECK(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW));
    }

    OpenGlVertexBuffer::~OpenGlVertexBuffer()
    {
        glDeleteBuffers(1, &mRendererId);
    }

    void OpenGlVertexBuffer::bind() const
    {
        GLCHECK(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
    }

    void OpenGlVertexBuffer::unBind() const
    {
        GLCHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    /*******************************Index Buffer**************************************/

    OpenGlIndexBuffer::OpenGlIndexBuffer(uint32_t *indices, uint32_t count)
        : mCount(count)
    {
        GLCHECK(glCreateBuffers(1, &mRendererId));

        // glCreateBuffers取代下面
        // glGenBuffers(1, &mRendererId);
        GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId));
        GLCHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
    }

    OpenGlIndexBuffer::~OpenGlIndexBuffer()
    {
        glDeleteBuffers(1, &mRendererId);
    }

    void OpenGlIndexBuffer::bind() const
    {
        GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId));
    }

    void OpenGlIndexBuffer::unBind() const
    {
        GLCHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

}