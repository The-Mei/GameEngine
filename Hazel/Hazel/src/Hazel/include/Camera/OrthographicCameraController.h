#pragma once

#include "Camera/OrthographicCamera.h"
#include "Core/Timestep.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Hazel
{
    class HAZEL_API OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool isRotation = false);

        void onUpdate(Timestep ts);

        void onEvent(Event &e);

        OrthographicCamera &getCamera() { return mCamera; }
        const OrthographicCamera &getCamera() const { return mCamera; }

    private:
        bool
        onMouseScrolled(MouseScrolledEvent &e);
        bool onWindowResize(WindowResizeEvent &e);

    private:
        float mAspectRatio;
        float mZoomLevel = 1.0f;
        OrthographicCamera mCamera;

        bool mRotation;
        glm::vec3 mCameraPosition = {0.0f, 0.0f, 0.0f};
        float mCameraRotation = 0.0f;

        float mCameraTranslateSpeed = 4.0f;
        float mCameraRotationSpeed = 180.0f;
    };
}