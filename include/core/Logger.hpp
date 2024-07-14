#pragma once

#include "pch.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "imgui.h"

template <>
struct fmt::formatter<ImVec4>
{
	constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

	template <typename FormatContext>
	auto format(const ImVec4 &vec, FormatContext &ctx)
	{
		return format_to(ctx.out(), "({},{},{},{})", vec.x, vec.y, vec.z, vec.w);
	}
};

namespace engine
{
	namespace core
	{
		enum class LogChannel
		{
			Engine = 0,
			App = 1,
			Scripting = 2
		};

		class Logger
		{
		public:
			static void Init();
			static void SetCallback(const std::function<void(LogChannel, const std::string &)> &callback);

			static void Trace(LogChannel channel, const std::string &message);
#ifndef NDEBUG
			static void Debug(LogChannel channel, const std::string &message);
#endif // NDEBUG
			static void Info(LogChannel channel, const std::string &message);
			static void Warn(LogChannel channel, const std::string &message);
			static void Error(LogChannel channel, const std::string &message);
			static void Critical(LogChannel channel, const std::string &message);

			static const std::vector<std::pair<LogChannel, std::string>> &GetMessages();
			static std::vector<std::pair<LogChannel, std::string>> s_Messages;

		private:
			static void Log(LogChannel channel, const std::string &message, const ImVec4 &color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

			static std::shared_ptr<spdlog::logger> s_EngineLogger;
			static std::shared_ptr<spdlog::logger> s_AppLogger;
			static std::shared_ptr<spdlog::logger> s_ScriptingLogger;
			static std::function<void(LogChannel, const std::string &)> s_Callback;
		};
	} // namespace core
} // namespace engine
