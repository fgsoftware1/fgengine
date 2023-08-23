#include "glad/glad.h"
#include "Window.hpp"
#include "Logger.hpp"

namespace engine
{
	namespace core
	{
		Window::Window(int width, int height, const std::string &title) : m_Width(width), m_Height(height), m_Title(title)
		{
			Init(width, height, title);
		}

		Window::~Window()
		{
			Shutdown();
		}

		void Window::Init(int width, int height, const std::string &title)
		{
			m_ShouldClose = false;

			if (!glfwInit())
			{
				Logger::Error(LogChannel::App, "Window can't be created, can't continue!");
				glfwTerminate();
				return;
			}

			m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			if (!m_Window)
			{
				Logger::Error(LogChannel::App, "Window creation failed, can't continue! :()");
				glfwTerminate();
				return;
			}

#ifndef NDEBUG
			Logger::Debug(LogChannel::Engine, "GLFW initialized!");
#endif // NDEBUG
			glfwMakeContextCurrent(m_Window);

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				Logger::Error(LogChannel::Engine, "Failed to initialize GLAD, can't continue! :(\n" + glad_glGetError());
				glfwTerminate();
			}
		}

		void Window::Shutdown()
		{
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		void Window::Update()
		{
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		void Window::setTitle(const std::string &title) { m_Title = title; }
		void Window::setSize(int width, int height)
		{
			m_Width = width;
			m_Height = height;
		}
		void Window::setVsync(bool vsync) { m_Vsync = vsync; }

		GLFWwindow *Window::getWindow()
		{
			return m_Window;
		}

		int Window::getWidth() { return m_Width; }
		int Window::getHeight() { return m_Height; }
		std::string Window::getTitle() { return m_Title; }
		bool Window::getVsync() { return m_Vsync; }
	} // namespace core
} // namespace engine