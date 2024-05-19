#include "Hzpch.h"

#include "Camera/OrthographicCameraController.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace Hazel
{
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool isRotation)
        : mAspectRatio(aspectRatio),
          mCamera(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel),
          mRotation(isRotation)
    {
    }

    void OrthographicCameraController::onUpdate(Timestep ts)
    {
        if (Input::isKeyPressed(HZ_KEY_A))
            mCameraPosition.x -= mCameraTranslateSpeed * ts;
        else if (Input::isKeyPressed(HZ_KEY_D))
            mCameraPosition.x += mCameraTranslateSpeed * ts;

        if (Input::isKeyPressed(HZ_KEY_W))
            mCameraPosition.y += mCameraTranslateSpeed * ts;
        else if (Input::isKeyPressed(HZ_KEY_S))
            mCameraPosition.y -= mCameraTranslateSpeed * ts;

        if (mRotation)
        {
            if (Input::isKeyPressed(HZ_KEY_Q))
                mCameraRotation += mCameraRotationSpeed * ts;
            else if (Input::isKeyPressed(HZ_KEY_E))
                mCameraRotation -= mCameraRotationSpeed * ts;

            mCamera.setRotation(mCameraRotation);
        }

        mCamera.setPosition(mCameraPosition);

        mCameraTranslateSpeed = mZoomLevel;
    }

    void OrthographicCameraController::onEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FN(OrthographicCameraController::onWindowResize));
    }

    bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent &e)
    {
        mZoomLevel -= e.getYOffset();
        mZoomLevel = std::max(mZoomLevel, 0.25f);
        mCamera.setProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
        return false;
    }

    bool OrthographicCameraController::onWindowResize(WindowResizeEvent &e)
    {
        mAspectRatio = (float)e.getWidth() / (float)e.getHeight();
        mCamera.setProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
        return false;
    }

}