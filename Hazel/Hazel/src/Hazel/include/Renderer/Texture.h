#pragma once

#include <string>
#include "Core/Core.h"

namespace Hazel
{
    class HAZEL_API Texture
    {
    public:
        virtual ~Texture() = default;
        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void bind(uint32_t slot = 0) const = 0;
        virtual void unBind() const = 0;

        virtual void setData(void *data, uint32_t size) = 0;
    };

    class HAZEL_API Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> create(uint32_t width, uint32_t height);
        static Ref<Texture2D> create(const std::string &path);
    };
}