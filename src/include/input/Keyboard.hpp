#pragma once

#include "KeyCode.h"

namespace fgengine {
	namespace graphics {
		class Window;
	}

	namespace input {
		class Keyboard
		{
			friend class graphics::Window;
		public:
			static bool CapsLock();
			static bool NumLock();

			static bool IsKeyDown(KeyCode key);
			static bool IsKeyUp(KeyCode key);
		private:
			static void KeyPressed(KeyCode key);
			static void KeyReleased(KeyCode key);
		private:
			static bool m_KeyboardState[256];
		};
	}
}