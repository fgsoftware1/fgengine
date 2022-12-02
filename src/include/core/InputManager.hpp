#pragma once

#include "../utils/Common.h"
#include "../utils/types.h"
#include "../math/Vector2.hpp"
#include "../input/Event.h"

using namespace std;
using namespace fgengine::input;
using namespace fgengine::math;

namespace fgengine {
	namespace core {
		#define MAX_KEYS	1024
		#define MAX_BUTTONS	32

		typedef function<void(Event& event)> WindowEventCallback;

		class Window;

		class FGE_API InputManager
		{
		private:
			friend class Window;
		private:
			bool m_KeyState[MAX_KEYS];
			bool m_LastKeyState[MAX_KEYS];
			bool m_MouseButtons[MAX_BUTTONS];
			bool m_MouseState[MAX_BUTTONS];
			bool m_MouseClicked[MAX_BUTTONS];
			bool m_MouseGrabbed;

			i32 m_KeyModifiers;
			Vector2 m_MousePosition;
			WindowEventCallback m_EventCallback;
		public:
			InputManager();

			inline void SetEventCallback(const WindowEventCallback& eventCallback) { m_EventCallback = eventCallback; }

			void Update();
			void PlatformUpdate();

			bool IsKeyPressed(uint keycode) const;
			bool IsMouseButtonPressed(uint button) const;
			bool IsMouseButtonClicked(uint button) const;

			const Vector2& GetMousePosition() const;
			void SetMousePosition(const Vector2& position);
			const bool IsMouseGrabbed() const;
			void SetMouseGrabbed(bool grabbed);
			void SetMouseCursor(i32 cursor);

			void ClearKeys();
			void ClearMouseButtons();
		private:
			friend void KeyCallback(InputManager* inputManager, i32 flags, i32 key, uint message);
			friend void MouseButtonCallback(InputManager* inputManager, i32 button, i32 x, i32 y);
		};

		class FGE_API Input
		{
		private:
			friend class InputManager;
		private:
			static InputManager* s_InputManager;
		public:
			inline static bool IsKeyPressed(uint keycode) { return s_InputManager->IsKeyPressed(keycode); }
			inline static bool IsMouseButtonPressed(uint button) { return s_InputManager->IsMouseButtonPressed(button); }
			inline static bool IsMouseButtonClicked(uint button) { return s_InputManager->IsMouseButtonClicked(button); }

			inline static const Vector2& GetMousePosition() { return s_InputManager->GetMousePosition(); }

			inline static InputManager* GetInputManager() { return s_InputManager; }
		};
	}
}

#define FGE_MOUSE_LEFT		0x00
#define FGE_MOUSE_MIDDLE	0x01
#define FGE_MOUSE_RIGHT		0x02

#define FGE_NO_CURSOR	  NULL

#define FGE_MODIFIER_LEFT_CONTROL	BIT(0)
#define FGE_MODIFIER_LEFT_ALT		BIT(1)
#define FGE_MODIFIER_LEFT_SHIFT		BIT(2)
#define FGE_MODIFIER_RIGHT_CONTROL	BIT(3)
#define FGE_MODIFIER_RIGHT_ALT		BIT(4)
#define FGE_MODIFIER_RIGHT_SHIFT	BIT(5)

#define FGE_KEY_TAB			  0x09
#define FGE_KEY_0			  0x30
#define FGE_KEY_1			  0x31
#define FGE_KEY_2			  0x32
#define FGE_KEY_3			  0x33
#define FGE_KEY_4			  0x34
#define FGE_KEY_5			  0x35
#define FGE_KEY_6			  0x36
#define FGE_KEY_7			  0x37
#define FGE_KEY_8			  0x38
#define FGE_KEY_9			  0x39
#define FGE_KEY_A			  0x41
#define FGE_KEY_B			  0x42
#define FGE_KEY_C			  0x43
#define FGE_KEY_D			  0x44
#define FGE_KEY_E			  0x45
#define FGE_KEY_F			  0x46
#define FGE_KEY_G			  0x47
#define FGE_KEY_H			  0x48
#define FGE_KEY_I			  0x49
#define FGE_KEY_J			  0x4A
#define FGE_KEY_K			  0x4B
#define FGE_KEY_L			  0x4C
#define FGE_KEY_M			  0x4D
#define FGE_KEY_N			  0x4E
#define FGE_KEY_O			  0x4F
#define FGE_KEY_P			  0x50
#define FGE_KEY_Q			  0x51
#define FGE_KEY_R			  0x52
#define FGE_KEY_S			  0x53
#define FGE_KEY_T			  0x54
#define FGE_KEY_U			  0x55
#define FGE_KEY_V			  0x56
#define FGE_KEY_W			  0x57
#define FGE_KEY_X			  0x58
#define FGE_KEY_Y			  0x59
#define FGE_KEY_Z			  0x5A
#define FGE_KEY_LBUTTON        0x01
#define FGE_KEY_RBUTTON        0x02
#define FGE_KEY_CANCEL         0x03
#define FGE_KEY_MBUTTON        0x04
#define FGE_KEY_ESCAPE         0x1B
#define FGE_KEY_SHIFT          0x10
#define FGE_KEY_CONTROL        0x11
#define FGE_KEY_MENU           0x12
#define FGE_KEY_ALT	          FGE_KEY_MENU
#define FGE_KEY_PAUSE          0x13
#define FGE_KEY_CAPITAL        0x14
#define FGE_KEY_FGEACE          0x20
#define FGE_KEY_PRIOR          0x21
#define FGE_KEY_NEXT           0x22
#define FGE_KEY_END            0x23
#define FGE_KEY_HOME           0x24
#define FGE_KEY_LEFT           0x25
#define FGE_KEY_UP             0x26
#define FGE_KEY_RIGHT          0x27
#define FGE_KEY_DOWN           0x28
#define FGE_KEY_SELECT         0x29
#define FGE_KEY_PRINT          0x2A
#define FGE_KEY_EXECUTE        0x2B
#define FGE_KEY_SNAPSHOT       0x2C
#define FGE_KEY_INSERT         0x2D
#define FGE_KEY_DELETE         0x2E
#define FGE_KEY_HELP           0x2F
#define FGE_KEY_NUMPAD0        0x60
#define FGE_KEY_NUMPAD1        0x61
#define FGE_KEY_NUMPAD2        0x62
#define FGE_KEY_NUMPAD3        0x63
#define FGE_KEY_NUMPAD4        0x64
#define FGE_KEY_NUMPAD5        0x65
#define FGE_KEY_NUMPAD6        0x66
#define FGE_KEY_NUMPAD7        0x67
#define FGE_KEY_NUMPAD8        0x68
#define FGE_KEY_NUMPAD9        0x69
#define FGE_KEY_MULTIPLY       0x6A
#define FGE_KEY_ADD            0x6B
#define FGE_KEY_SEPARATOR      0x6C
#define FGE_KEY_SUBTRACT       0x6D
#define FGE_KEY_DECIMAL        0x6E
#define FGE_KEY_DIVIDE         0x6F
#define FGE_KEY_F1             0x70
#define FGE_KEY_F2             0x71
#define FGE_KEY_F3             0x72
#define FGE_KEY_F4             0x73
#define FGE_KEY_F5             0x74
#define FGE_KEY_F6             0x75
#define FGE_KEY_F7             0x76
#define FGE_KEY_F8             0x77
#define FGE_KEY_F9             0x78
#define FGE_KEY_F10            0x79
#define FGE_KEY_F11            0x7A
#define FGE_KEY_F12            0x7B
#define FGE_KEY_F13            0x7C
#define FGE_KEY_F14            0x7D
#define FGE_KEY_F15            0x7E
#define FGE_KEY_F16            0x7F
#define FGE_KEY_F17            0x80
#define FGE_KEY_F18            0x81
#define FGE_KEY_F19            0x82
#define FGE_KEY_F20            0x83
#define FGE_KEY_F21            0x84
#define FGE_KEY_F22            0x85
#define FGE_KEY_F23            0x86
#define FGE_KEY_F24            0x87
#define FGE_KEY_NUMLOCK        0x90
#define FGE_KEY_SCROLL         0x91
#define FGE_KEY_LSHIFT         0xA0
#define FGE_KEY_RSHIFT         0xA1
#define FGE_KEY_LCONTROL       0xA2
#define FGE_KEY_RCONTROL       0xA3
#define FGE_KEY_LMENU          0xA4
#define FGE_KEY_RMENU          0xA5