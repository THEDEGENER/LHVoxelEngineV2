#include "Logging.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Core
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_AppLogger;

    void Log::Init()
    {

        s_CoreLogger = spdlog::stdout_color_mt("CORE");
        s_CoreLogger->set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_AppLogger = spdlog::stdout_color_mt("APP");
        s_AppLogger->set_level(spdlog::level::trace);
        s_AppLogger->set_pattern("%^[%T] %n : %v%$");
    }
}