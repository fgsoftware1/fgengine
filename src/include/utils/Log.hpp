#pragma once

#include "../utils/Common.h"
#include "../utils/types.h"
#include "../math/Vector2.hpp"
#include "../math/Rectangle.hpp"
#include "../input/KeyEvent.h"

#define FGE_LOG_LEVEL_FATAL 0
#define FGE_LOG_LEVEL_ERROR 1
#define FGE_LOG_LEVEL_WARN  2
#define FGE_LOG_LEVEL_INFO  3

#ifdef MOUSE_MOVED
	#undef MOUSE_MOVED
#endif

using namespace fgengine::input;
using namespace fgengine::utils;

nameFGEace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return string("[Unsupported type (") + typeid(T).name() + string(")!] (to_string)");
	}
}

namespace fgengine {
	namespace internal {
		static char to_string_buffer[1024 * 10];
		static char sprintf_buffer[1024 * 10];

		FGE_API void PlatformLogMessage(uint level, const char* message);

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};

		template <typename T>
		static const char* to_string(const T& t)
		{
			return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
		}

		template <>
		static const char* to_string<char>(const char& t)
		{
			return &t;
		}

		template <>
		static const char* to_string<char*>(char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const& t)
		{
			return (const char*)t;
		}

		template <>
		static const char* to_string<wchar_t*>(wchar_t* const& t)
		{
			wcstombs(FGErintf_buffer, t, 1024 * 10);
			return FGErintf_buffer;
		}

		template <>
		static const char* to_string<const wchar_t*>(const wchar_t* const& t)
		{
			wcstombs(FGErintf_buffer, t, 1024 * 10);
			return FGErintf_buffer;
		}

		template <>
		static const char* to_string<const char*>(const char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<String>(const String& t)
		{
			return t.c_str();
		}

		template <>
		static const char* to_string<bool>(const bool& t)
		{
			return t ? "true" : "false";
		}

		template <>
		static const char* to_string<math::Vector2>(const math::Vector2& t)
		{
			String string = String("Vector2: (") + StringFormat::ToString(t.x) + ", " + StringFormat::ToString(t.y) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

		template <>
		static const char* to_string<maths::vec3>(const math::Vector3& t)
		{
			String string = String("Vector3: (") + StringFormat::ToString(t.x) + ", " + StringFormat::ToString(t.y) + ", " + StringFormat::ToString(t.z) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

		template <>
		static const char* to_string<math::Rectangle>(const math::Rectangle& r)
		{
			FGErintf(FGErintf_buffer, "Rectangle: (%f, %f, %f, %f)", r.x, r.y, r.width, r.height);
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<KeyPressedEvent>(const KeyPressedEvent& e)
		{
			FGErintf(FGErintf_buffer, "KeyPressedEvent: (%d, %d)", e.GetKeyCode(), e.GetRepeat());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::KeyReleasedEvent>(const events::KeyReleasedEvent& e)
		{
			FGErintf(FGErintf_buffer, "KeyReleasedEvent: (%d)", e.GetKeyCode());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::MousePressedEvent>(const events::MousePressedEvent& e)
		{
			FGErintf(FGErintf_buffer, "MousePressedEvent: (%d, %f, %f)", e.GetButton(), e.GetX(), e.GetY());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::MouseReleasedEvent>(const events::MouseReleasedEvent& e)
		{
			FGErintf(FGErintf_buffer, "MouseReleasedEvent: (%d, %f, %f)", e.GetButton(), e.GetX(), e.GetY());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::MouseMovedEvent>(const events::MouseMovedEvent& e)
		{
			FGErintf(FGErintf_buffer, "MouseMovedEvent: (%f, %f, %s)", e.GetX(), e.GetY(), e.IsDragged() ? "true" : "false");
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::Event>(const events::Event& e)
		{
			FGErintf(FGErintf_buffer, "Event: %s (%d)", events::Event::TypeToString(e.GetType()).c_str(), e.GetType());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<input::Event*>(input::Event* const& e)
		{
			using nameFGEace events;

			switch (e->GetType())
			{
			case Event::Type::KEY_PRESSED:
				return to_string(*(KeyPressedEvent*)e);
			case Event::Type::KEY_RELEASED:
				return to_string(*(KeyReleasedEvent*)e);
			case Event::Type::MOUSE_PRESSED:
				return to_string(*(MousePressedEvent*)e);
			case Event::Type::MOUSE_RELEASED:
				return to_string(*(MouseReleasedEvent*)e);
			case Event::Type::MOUSE_MOVED:
				return to_string(*(MouseMovedEvent*)e);
			}
			return "Unkown Event!";
		}

		template <typename T>
		static String format_iterators(T& begin, T& end)
		{
			String result;
			bool first = true;
			while (begin != end)
			{
				if (!first)
					result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}

		template <typename T>
		static const char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			FGErintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static const char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = StringFormat::ToString(t);
			return strcpy(to_string_buffer, x.c_str());
		}

		template<typename X, typename Y>
		static const char* to_string(const std::pair<typename X, typename Y>& v)
		{
			FGErintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
			return to_string_buffer;
		}

		template<>
		static const char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return v;
		}

		template <typename First>
		static void print_log_internal(char* buffer, i32& position, First&& first)
		{
			const char* formatted = FGE::internal::to_string<First>(first);
			i32 length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, i32& position, First&& first, Args&&... args)
		{
			const char* formatted = FGE::internal::to_string<First>(first);
			i32 length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
				print_log_internal(buffer, position, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void log_message(i32 level, bool newline, Args... args)
		{
			char buffer[1024 * 10];
			i32 position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			if (newline)
				buffer[position++] = '\n';

			buffer[position] = 0;

			PlatformLogMessage(level, buffer);
		}
	}
}

// Windows (wingdi.h) defines FGE_ERROR
#ifdef FGE_ERROR
#undef FGE_ERROR
#endif

#ifndef FGE_LOG_LEVEL
#define FGE_LOG_LEVEL FGE_LOG_LEVEL_INFO
#endif

#if FGE_LOG_LEVEL >= FGE_LOG_LEVEL_FATAL
#define FGE_FATAL(...) FGE::internal::log_message(FGE_LOG_LEVEL_FATAL, true, "FGE:    ", __VA_ARGS__)
#define _FGE_FATAL(...) FGE::internal::log_message(FGE_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define FGE_FATAL(...)
#define _FGE_FATAL(...)
#endif

#if FGE_LOG_LEVEL >= FGE_LOG_LEVEL_ERROR
#define FGE_ERROR(...) FGE::internal::log_message(FGE_LOG_LEVEL_ERROR, true, "FGE:    ", __VA_ARGS__)
#define _FGE_ERROR(...) FGE::internal::log_message(FGE_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
#define FGE_ERROR(...)
#define _FGE_ERROR(...)
#endif

#if FGE_LOG_LEVEL >= FGE_LOG_LEVEL_WARN
#define FGE_WARN(...) FGE::internal::log_message(FGE_LOG_LEVEL_WARN, true, "FGE:    ", __VA_ARGS__)
#define _FGE_WARN(...) FGE::internal::log_message(FGE_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
#define FGE_WARN(...)
#define _FGE_WARN(...)
#endif

#if FGE_LOG_LEVEL >= FGE_LOG_LEVEL_INFO
#define FGE_INFO(...) FGE::internal::log_message(FGE_LOG_LEVEL_INFO, true, "FGE:    ", __VA_ARGS__)
#define _FGE_INFO(...) FGE::internal::log_message(FGE_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
#define FGE_INFO(...)
#define _FGE_INFO(...)
#endif

#ifdef FGE_DEBUG
#define FGE_ASSERT(x, ...) \
		if (!(x)) {\
			FGE_FATAL("*************************"); \
			FGE_FATAL("    ASSERTION FAILED!    "); \
			FGE_FATAL("*************************"); \
			FGE_FATAL(__FILE__, ": ", __LINE__); \
			FGE_FATAL("Condition: ", #x); \
			FGE_FATAL(__VA_ARGS__); \
			__debugbreak(); \
		}
#else
#define FGE_ASSERT(x, ...)
#endif#pragma once

#include "FGE/Common.h"
#include "FGE/Types.h"

#include "FGE/maths/vec2.h"
#include "FGE/maths/Rectangle.h"
#include "FGE/events/Events.h"

#define FGE_LOG_LEVEL_FATAL 0
#define FGE_LOG_LEVEL_ERROR 1
#define FGE_LOG_LEVEL_WARN  2
#define FGE_LOG_LEVEL_INFO  3

#ifdef MOUSE_MOVED
#undef MOUSE_MOVED // Defined in wincon.h
#endif

nameFGEace std
{
	template <typename T>
	string to_string(const T& t)
	{
		return string("[Unsupported type (") + typeid(T).name() + string(")!] (to_string)");
	}
}

//
// Work in progress!
//
// -------------------------------
//			TODO: 
// -------------------------------
//	- Better container type logging
//	- Better platform support
//	- Logging to other destinations (eg. files)
//	- Include (almost) ALL FGE class types
//	- More...
nameFGEace FGE {
	nameFGEace internal {

		static char to_string_buffer[1024 * 10];
		static char FGErintf_buffer[1024 * 10];

		FGE_API void PlatformLogMessage(uint level, const char* message);

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};

		template <typename T>
		static const char* to_string(const T& t)
		{
			return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
		}

		template <>
		static const char* to_string<char>(const char& t)
		{
			return &t;
		}

		template <>
		static const char* to_string<char*>(char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const& t)
		{
			return (const char*)t;
		}

		template <>
		static const char* to_string<wchar_t*>(wchar_t* const& t)
		{
			wcstombs(FGErintf_buffer, t, 1024 * 10);
			return FGErintf_buffer;
		}

		template <>
		static const char* to_string<const wchar_t*>(const wchar_t* const& t)
		{
			wcstombs(FGErintf_buffer, t, 1024 * 10);
			return FGErintf_buffer;
		}

		template <>
		static const char* to_string<const char*>(const char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<String>(const String& t)
		{
			return t.c_str();
		}

		template <>
		static const char* to_string<bool>(const bool& t)
		{
			return t ? "true" : "false";
		}

		template <>
		static const char* to_string<maths::vec2>(const maths::vec2& t)
		{
			// TODO: FGErintf
			String string = String("vec2: (") + StringFormat::ToString(t.x) + ", " + StringFormat::ToString(t.y) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

		template <>
		static const char* to_string<maths::vec3>(const maths::vec3& t)
		{
			// TODO: FGErintf
			String string = String("vec3: (") + StringFormat::ToString(t.x) + ", " + StringFormat::ToString(t.y) + ", " + StringFormat::ToString(t.z) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

		template <>
		static const char* to_string<maths::Rectangle>(const maths::Rectangle& r)
		{
			FGErintf(FGErintf_buffer, "Rectangle: (%f, %f, %f, %f)", r.x, r.y, r.width, r.height);
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::KeyPressedEvent>(const events::KeyPressedEvent& e)
		{
			FGErintf(FGErintf_buffer, "KeyPressedEvent: (%d, %d)", e.GetKeyCode(), e.GetRepeat());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::KeyReleasedEvent>(const events::KeyReleasedEvent& e)
		{
			FGErintf(FGErintf_buffer, "KeyReleasedEvent: (%d)", e.GetKeyCode());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::MousePressedEvent>(const events::MousePressedEvent& e)
		{
			FGErintf(FGErintf_buffer, "MousePressedEvent: (%d, %f, %f)", e.GetButton(), e.GetX(), e.GetY());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::MouseReleasedEvent>(const events::MouseReleasedEvent& e)
		{
			FGErintf(FGErintf_buffer, "MouseReleasedEvent: (%d, %f, %f)", e.GetButton(), e.GetX(), e.GetY());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::MouseMovedEvent>(const events::MouseMovedEvent& e)
		{
			FGErintf(FGErintf_buffer, "MouseMovedEvent: (%f, %f, %s)", e.GetX(), e.GetY(), e.IsDragged() ? "true" : "false");
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::Event>(const events::Event& e)
		{
			FGErintf(FGErintf_buffer, "Event: %s (%d)", events::Event::TypeToString(e.GetType()).c_str(), e.GetType());
			char* result = new char[strlen(FGErintf_buffer)];
			strcpy(result, &FGErintf_buffer[0]);
			return result;
		}

		template <>
		static const char* to_string<events::Event*>(events::Event* const& e)
		{
			using nameFGEace events;

			switch (e->GetType())
			{
			case Event::Type::KEY_PRESSED:
				return to_string(*(KeyPressedEvent*)e);
			case Event::Type::KEY_RELEASED:
				return to_string(*(KeyReleasedEvent*)e);
			case Event::Type::MOUSE_PRESSED:
				return to_string(*(MousePressedEvent*)e);
			case Event::Type::MOUSE_RELEASED:
				return to_string(*(MouseReleasedEvent*)e);
			case Event::Type::MOUSE_MOVED:
				return to_string(*(MouseMovedEvent*)e);
			}
			return "Unkown Event!";
		}

		template <typename T>
		static String format_iterators(T& begin, T& end)
		{
			String result;
			bool first = true;
			while (begin != end)
			{
				if (!first)
					result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}

		template <typename T>
		static const char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			FGErintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static const char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = StringFormat::ToString(t);
			return strcpy(to_string_buffer, x.c_str());
		}

		template<typename X, typename Y>
		static const char* to_string(const std::pair<typename X, typename Y>& v)
		{
			FGErintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
			return to_string_buffer;
		}

		template<>
		static const char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return v;
		}

		template <typename First>
		static void print_log_internal(char* buffer, i32& position, First&& first)
		{
			const char* formatted = FGE::internal::to_string<First>(first);
			i32 length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, i32& position, First&& first, Args&&... args)
		{
			const char* formatted = FGE::internal::to_string<First>(first);
			i32 length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
				print_log_internal(buffer, position, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void log_message(i32 level, bool newline, Args... args)
		{
			char buffer[1024 * 10];
			i32 position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			if (newline)
				buffer[position++] = '\n';

			buffer[position] = 0;

			PlatformLogMessage(level, buffer);
		}
	}
}

#ifdef FGE_ERROR
	#undef FGE_ERROR
#endif

#ifndef FGE_LOG_LEVEL
#define FGE_LOG_LEVEL FGE_LOG_LEVEL_INFO
#endif

#if FGE_LOG_LEVEL >= FGE_LOG_LEVEL_FATAL
#define FGE_FATAL(...) FGE::internal::log_message(FGE_LOG_LEVEL_FATAL, true, "FGE:    ", __VA_ARGS__)
#define _FGE_FATAL(...) FGE::internal::log_message(FGE_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define FGE_FATAL(...)
#define _FGE_FATAL(...)
#endif

#if FGE_LOG_LEVEL >= FGE_LOG_LEVEL_ERROR
#define FGE_ERROR(...) FGE::internal::log_message(FGE_LOG_LEVEL_ERROR, true, "FGE:    ", __VA_ARGS__)
#define _FGE_ERROR(...) FGE::internal::log_message(FGE_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
#define FGE_ERROR(...)
#define _FGE_ERROR(...)
#endif

#if FGE_LOG_LEVEL >= FGE_LOG_LEVEL_WARN
#define FGE_WARN(...) FGE::internal::log_message(FGE_LOG_LEVEL_WARN, true, "FGE:    ", __VA_ARGS__)
#define _FGE_WARN(...) FGE::internal::log_message(FGE_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
#define FGE_WARN(...)
#define _FGE_WARN(...)
#endif

#if FGE_LOG_LEVEL >= FGE_LOG_LEVEL_INFO
#define FGE_INFO(...) FGE::internal::log_message(FGE_LOG_LEVEL_INFO, true, "FGE:    ", __VA_ARGS__)
#define _FGE_INFO(...) FGE::internal::log_message(FGE_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
#define FGE_INFO(...)
#define _FGE_INFO(...)
#endif

#ifdef FGE_DEBUG
#define FGE_ASSERT(x, ...) \
		if (!(x)) {\
			FGE_FATAL("*************************"); \
			FGE_FATAL("    ASSERTION FAILED!    "); \
			FGE_FATAL("*************************"); \
			FGE_FATAL(__FILE__, ": ", __LINE__); \
			FGE_FATAL("Condition: ", #x); \
			FGE_FATAL(__VA_ARGS__); \
			__debugbreak(); \
		}
#else
#define FGE_ASSERT(x, ...)
#endif