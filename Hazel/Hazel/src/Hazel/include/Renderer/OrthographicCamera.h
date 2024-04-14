#pragma once

#include "glm.hpp"

namespace Hazel
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        ~OrthographicCamera();

        void setPosition(const glm::vec3 &position)
        {
            mPosition = position;
            RecalculateViewMatrix();
        }
        const glm::vec3 &getPosition() const { return mPosition; }
        void setRotation(float rotation)
        {
            mRotation = rotation;
            RecalculateViewMatrix();
        }
        float getRotation() const { return mRotation; }

        const glm::mat4 &getProjectMatrix() const { return mProjectMatrix; }
        const glm::mat4 &getViewMatrix() const { return mViewMatrix; }
        const glm::mat4 &getViewProjectMatrix() const { return mViewProjectMatrix; }

    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 mProjectMatrix;
        glm::mat4 mViewMatrix;
        glm::mat4 mViewProjectMatrix;

        glm::vec3 mPosition = {0.0, 0.0, 0.0};
        float mRotation = 0.0f;
    };

}