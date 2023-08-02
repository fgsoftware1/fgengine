#pragma once

#include "pch.hpp"
#include "GLFW/glfw3.h"

namespace engine
{
	namespace core
	{
		class Window
		{
		public:
			Window() = default;
			Window(int width, int height, const std::string &title);
			~Window();

			void Init(int width, int height, const std::string &title);
			void Shutdown();
			void Update();

			void setTitle(const std::string &title);
			void setIcon(const std::string &icon);
			void setSize(int width, int height);
			void setVsync(bool vsync);

			GLFWwindow *getWindow();
			int getWidth();
			int getHeight();
			std::string getTitle();
			std::string getIcon();
			bool getVsync();

		private:
			GLFWwindow *m_Window;
			int m_Width;
			int m_Height;
			std::string m_Title;
			bool m_Vsync;
			bool m_ShouldClose;
		};
	} // namespace core
} // namespace engine