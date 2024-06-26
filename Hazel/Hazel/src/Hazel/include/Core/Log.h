#pragma once

#define SPDLOG_ACTIVE_LEVEL 0

#include "Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

// Core Log
#define LOGT(...) SPDLOG_LOGGER_TRACE(::Hazel::Log::getCoreLogger(), __VA_ARGS__)
#define LOGD(...) SPDLOG_LOGGER_DEBUG(::Hazel::Log::getCoreLogger(), __VA_ARGS__)
#define LOGI(...) SPDLOG_LOGGER_INFO(::Hazel::Log::getCoreLogger(), __VA_ARGS__)
#define LOGW(...) SPDLOG_LOGGER_WARN(::Hazel::Log::getCoreLogger(), __VA_ARGS__)
#define LOGE(...) SPDLOG_LOGGER_ERROR(::Hazel::Log::getCoreLogger(), __VA_ARGS__)
// #define LOGF(...) ::Hazel::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client Log
// #define LOGCT(...) ::Hazel::Log::getClientgLogger()->trace(__VA_ARGS__)
#define LOGCT(...) SPDLOG_LOGGER_TRACE(::Hazel::Log::getClientgLogger(), __VA_ARGS__)
#define LOGCD(...) SPDLOG_LOGGER_DEBUG(::Hazel::Log::getClientgLogger(), __VA_ARGS__)
#define LOGCI(...) SPDLOG_LOGGER_INFO(::Hazel::Log::getClientgLogger(), __VA_ARGS__)
#define LOGCW(...) SPDLOG_LOGGER_WARN(::Hazel::Log::getClientgLogger(), __VA_ARGS__)
#define LOGCE(...) SPDLOG_LOGGER_ERROR(::Hazel::Log::getClientgLogger(), __VA_ARGS__)
// #define LOGCF(...) (::Hazel::Log::getClientgLogger(), __VA_ARGS__)

#define LOGTMP(msg, ...) Hazel::Log::logTmp("[%s:%s:%d]" msg, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
namespace Hazel
{
    class HAZEL_API Log
    {
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger> &getCoreLogger() { return mCoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &getClientgLogger() { return mClientLogger; }

        static void logTmp(const char *fmt, ...)
        {
            char msg[1024] = {};
            va_list arg;
            va_start(arg, fmt);
            vsprintf(msg, fmt, arg);
            va_end(arg);
            char *pos = strrchr(msg, '\\');
            if (pos)
            {
                int position = pos - msg + 1;
                LOGI("{0}", &msg[position]);
            }
        }

    private:
        static std::shared_ptr<spdlog::logger> mCoreLogger;
        static std::shared_ptr<spdlog::logger> mClientLogger;
    };
}