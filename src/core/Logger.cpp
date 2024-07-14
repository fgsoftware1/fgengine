#include "spdlog/sinks/stdout_color_sinks.h"
#include "magic_enum.hpp"

#include "core/Logger.hpp"

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
			std::cout <<  "\033[90m" << magic_enum::enum_name(channel) << ": " << message.c_str() << "\033[0m" << std::endl;
			Log(channel, message, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

#ifndef NDEBUG
		void Logger::Debug(LogChannel channel, const std::string &message)
		{
			std::cout << "\033[34m" << magic_enum::enum_name(channel) << ": " << message.c_str() << "\033[0m" <<  std::endl;
			Log(channel, message, ImVec4(0.2f, 0.8f, 0.2f, 1.0f)); // Green
		}
#endif // NDEBUG

		void Logger::Info(LogChannel channel, const std::string &message)
		{
			std::cout << "\033[32m" << magic_enum::enum_name(channel) << ": " << message.c_str() << "\033[0m" << std::endl;
			Log(channel, message, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // White
		}

		void Logger::Warn(LogChannel channel, const std::string &message)
		{
			std::cout << "\033[33m" << magic_enum::enum_name(channel) << ": " << message.c_str() << "\033[0m" << std::endl;
			Log(channel, message, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); // Yellow
		}

		void Logger::Error(LogChannel channel, const std::string &message)
		{
			std::cout << "\033[31m" << magic_enum::enum_name(channel) << ": " << message.c_str() << "\033[0m" << std::endl;
			Log(channel, message, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red
		}

		void Logger::Critical(LogChannel channel, const std::string &message)
		{
			std::cout << "\033[1;31m" << magic_enum::enum_name(channel) << ": " << message.c_str() << "\033[0m" << std::endl;
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
				textColor.w * color.w);

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
