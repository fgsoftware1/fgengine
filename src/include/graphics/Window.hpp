#pragma once

#include <functional>
#include <map>

#include "../input/Event.h"
#include "../utils/types.h"
#include "../utils/utils.h"
#include "../math/Vector2.hpp"
#include "../core/InputManager.hpp"

namespace fgengine {
	namespace graphics {
		typedef std::function<void(input::Event & event)> WindowEventCallback;

		struct FGE_API WindowProperties
		{
			uint width, height;
			bool fullscreen;
			bool vsync;
		};

		class FGE_API Window
		{
		private:
			static std::map<void*, Window*> s_Handles;
		private:
			String m_Title;
			WindowProperties m_Properties;
			bool m_Closed;
			void* m_Handle;

			bool m_Vsync;
			WindowEventCallback m_EventCallback;
			core::InputManager* m_InputManager;
		public:
			Window(const String& name, const WindowProperties& properties);
			~Window();
			void Clear() const;
			void Update();
			bool Closed() const;

			void SetTitle(const String& title);

			inline uint GetWidth() const { return m_Properties.width; }
			inline uint GetHeight() const { return m_Properties.height; }

			void SetVsync(bool enabled);
			inline bool IsVsync() const { return m_Vsync; }

			inline core::InputManager* GetInputManager() const { return m_InputManager; }

			void SetEventCallback(const WindowEventCallback& callback);
		private:
			bool Init();

			bool PlatformInit();
			void PlatformUpdate();

			friend void ResizeCallback(Window* window, i32 width, i32 height);
			friend void FocusCallback(Window* window, bool focused);
		public:
			static void RegisterWindowClass(void* handle, Window* window);
			static Window* GetWindowClass(void* handle);
		};
	}
}