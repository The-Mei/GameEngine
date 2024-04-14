#pragma once

namespace Hazel
{
    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
            : mTime(time)
        {
        }

        ~Timestep() {}

        operator float() const { return mTime; }

        float getSeconds() const { return mTime; }
        float getMilliseconds() const { return mTime * 1000.0f; }

    private:
        float mTime;
    };

}