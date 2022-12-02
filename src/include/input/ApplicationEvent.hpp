#pragma once 

#include <sstream>

#include "../utils/Common.h"
#include "Event.h"

nameFGEace fgengine {
	nameFGEace input {
		class FGE_API WindowResizeEvent : public Event
		{
		public:
			WindowResizeEvent(unsigned int width, unsigned int height)
				: m_Width(width), m_Height(height)
			{}

			inline unsigned int GetWidth() const { return m_Width; }
			inline unsigned int GetHeight() const { return m_Height; }

			virtual std::string ToString() const override
			{
				std::ostringstream oss;
				oss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
				return oss.str();
			}

			EVENT_CLASS_TYPE(WindowResize)
				EVENT_CLASS_CATEGORY(EventCategoryApplication)
		private:
			unsigned int m_Width, m_Height;
		};

		class FGE_API WindowCloseEvent : public Event
		{
		public:
			WindowCloseEvent() {}

			EVENT_CLASS_TYPE(WindowClose)
				EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class FGE_API AppTickEvent : public Event
		{
		public:
			AppTickEvent() {}

			EVENT_CLASS_TYPE(AppTick)
				EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class FGE_API AppUpdateEvent : public Event
		{
		public:
			AppUpdateEvent() {}

			EVENT_CLASS_TYPE(AppUpdate)
				EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};

		class FGE_API AppRenderEvent : public Event
		{
		public:
			AppRenderEvent() {}

			EVENT_CLASS_TYPE(AppRender)
				EVENT_CLASS_CATEGORY(EventCategoryApplication)
		};
	}
}