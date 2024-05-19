#pragma once

#include "Core/Core.h"
#include "Events/Event.h"

#include "Core/Timestep.h"

namespace Hazel
{
    class HAZEL_API Layer
    {
    public:
        Layer(const std::string &name = "Layer");
        virtual ~Layer();

        virtual void onAttach() {}
        virtual void onDetach() {}
        virtual void onUpdate(Timestep ts) {}
        virtual void onImGuiRender() {}
        virtual void onEvent(Event &event) {}

        inline const std::string &getName() const { return mDebugName; }

    private:
        std::string mDebugName;
    };
}