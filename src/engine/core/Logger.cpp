#include "Logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace engine
{
    namespace core
    {
        std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
        std::shared_ptr<spdlog::logger> Logger::s_AppLogger;
        std::shared_ptr<spdlog::logger> Logger::s_ScriptingLogger;
        std::function<void(LogChannel, const std::string &)> Logger::s_Callback;
        std::vector<std::pair<LogChannel, std::string>> Logger::s_Messages;

        void Logger::Init()
        {
            spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
            s_EngineLogger = spdlog::stdout_color_mt("ENGINE");
            s_AppLogger = spdlog::stdout_color_mt("APP");
            s_ScriptingLogger = spdlog::stdout_color_mt("SCRIPTING");
            spdlog::set_level(spdlog::level::trace);
        }

        void Logger::SetCallback(const std::function<void(LogChannel, const std::string &)> &callback)
        {
            s_Callback = callback;
        }

        void Logger::Trace(LogChannel channel, const std::string &message)
        {
            Log(channel, message, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White
        }

        void Logger::Debug(LogChannel channel, const std::string &message)
        {
            Log(channel, message, ImVec4(0.2f, 0.8f, 0.2f, 1.0f)); // Green
        }

        void Logger::Info(LogChannel channel, const std::string &message)
        {
            Log(channel, message, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White
        }

        void Logger::Warn(LogChannel channel, const std::string &message)
        {
            Log(channel, message, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); // Yellow
        }

        void Logger::Error(LogChannel channel, const std::string &message)
        {
            Log(channel, message, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red
        }

        void Logger::Critical(LogChannel channel, const std::string &message)
        {
            Log(channel, message, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red
        }

        void Logger::Log(LogChannel channel, const std::string &message, const ImVec4 &color)
        {
            ImVec4 textColor;
            switch (channel)
            {
            case LogChannel::Engine:
                textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            case LogChannel::App:
                textColor = ImVec4(0.2f, 0.8f, 0.2f, 1.0f);
                break;
            case LogChannel::Scripting:
                textColor = ImVec4(0.8f, 0.2f, 0.2f, 1.0f);
                break;
            default:
                textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                break;
            }

            ImVec4 finalColor = ImVec4(
                textColor.x * color.x,
                textColor.y * color.y,
                textColor.z * color.z,
                textColor.w * color.w
            );

            s_Messages.emplace_back(channel, fmt::format("{1}", finalColor, message));

            if (s_Callback)
                s_Callback(channel, message);
        }

        const std::vector<std::pair<LogChannel, std::string>> &Logger::GetMessages()
        {
            return s_Messages;
        }
    } // namespace core
} // namespace engine