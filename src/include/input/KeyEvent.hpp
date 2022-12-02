#pragma once

#include "Event.h"
#pragma once 

#include "../utils/Common.h"
#include "KeyCode.h"

namespace fgengine {
	namespace input {
		class FGE_API KeyEvent : public Event
		{
		public:
			KeyCode GetKeyCode() const { return m_KeyCode; }

			EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		protected:
			KeyEvent(const KeyCode keycode)
				: m_KeyCode(keycode) {}

			KeyCode m_KeyCode;
		};

		class FGE_API KeyPressedEvent : public KeyEvent
		{
		public:
			KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
				: KeyEvent(keycode), m_IsRepeat(isRepeat) {}

			bool IsRepeat() const { return m_IsRepeat; }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyPressed)
		private:
			bool m_IsRepeat;
		};

		class FGE_API KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(const KeyCode keycode)
				: KeyEvent(keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyReleasedEvent: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyReleased)
		};

		class FGE_API KeyTypedEvent : public KeyEvent
		{
		public:
			KeyTypedEvent(const KeyCode keycode)
				: KeyEvent(keycode) {}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyTypedEvent: " << m_KeyCode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(KeyTyped)
		};
	}
}