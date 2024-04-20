#pragma once

#include <memory>

#ifdef HZ_PLATFROM_WINDOWS
#ifdef HZ_BUILD_DLL
#define HAZEL_API __declspec(dllexport) //__attribute__((visibility("default")))
#else
#define HAZEL_API __declspec(dllimport)
#endif
#else
#error Hazel only support Windows!
#endif

#ifdef HZ_ENABLE_ASSERTS
#define HZ_ASSERT(x, ...)                                \
    {                                                    \
        if (!x)                                          \
        {                                                \
            LOGCE("Assertion Failed: {0}", __VA_ARGS__); \
            __debugbreak();                              \
        }                                                \
    }
#define HZ_CORE_ASSERT(x, ...)                          \
    {                                                   \
        if (!x)                                         \
        {                                               \
            LOGE("Assertion Failed: {0}", __VA_ARGS__); \
            __debugbreak();                             \
        }                                               \
    }
#else
#define HZ_ASSERT(x, ...)
#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T>
    using Ref = std::shared_ptr<T>;
}