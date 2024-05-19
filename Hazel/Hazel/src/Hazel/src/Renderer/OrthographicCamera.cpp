#include "Hzpch.h"

#include "Renderer/OrthographicCamera.h"

#include "gtc/matrix_transform.hpp"

namespace Hazel
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : mProjectMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), mViewMatrix(1.0f)
    {
        mViewProjectMatrix = mProjectMatrix * mViewMatrix;
    }

    OrthographicCamera::~OrthographicCamera() {}

    void OrthographicCamera::setProjection(float left, float right, float bottom, float top)
    {
        mProjectMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        mViewProjectMatrix = mProjectMatrix * mViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition) * glm::rotate(glm::mat4(1.0f), glm::radians(mRotation), glm::vec3(0, 0, 1));

        // transform = glm::rotate(transform, glm::radians(mRotation), glm::vec3(0, 0, 1));

        mViewMatrix = glm::inverse(transform);

        mViewProjectMatrix = mProjectMatrix * mViewMatrix;
    }
}