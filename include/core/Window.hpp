#pragma once

#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"

#include "pch.hpp"

namespace engine
{
	namespace core
	{
		class Window
		{
		public:
			int windowWidth, windowHeight;
			std::string windowTitle;
			GLFWwindow* windowHandle;

		public:
			Window();
			Window(int width, int height, std::string title);

			int Run();

		protected:
			virtual void Init() = 0;
			virtual void Load() = 0;
			virtual void Render() = 0;
			virtual void Update() = 0;
			virtual void Unload() = 0;
			virtual void Shutdown() = 0;
		};
	} // namespace core
} // namespace engine