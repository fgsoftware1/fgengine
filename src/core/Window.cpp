// #include "glad/glad.h"
// #include "GLFW/glfw3.h"

// #include "core/Window.hpp"
// #include "core/Logger.hpp"

// using namespace engine::core;

// void errorCallback(int error, const char* description) {
	
// }

// namespace engine
// {
// 	namespace core
// 	{
// 		Window::Window(){}

// 		Window::Window(int width, int height, std::string title)
// 		{
// 			this->windowWidth = width;
// 			this->windowHeight = height;
// 			this->windowTitle = title;
// 		}

// 		int Window::Run()
// 		{
// 			if (!glfwInit()) {
// 				Logger::Critical(LogChannel::Engine, "Failed to initialize GLFW :(");
// 				return -1;
// 			}
// 			else {
// #ifndef NDEBUG
// 				Logger::Debug(LogChannel::Engine, "GLFW initialized!");
// #endif // !NDEBUG
// 				glfwSetErrorCallback(errorCallback);
// 			}

// 			if (this->windowWidth <= 0 || this->windowHeight <= 0) {
// 				Logger::Critical(LogChannel::Engine, "Invalid window dimensions");
// 				glfwTerminate();
// 				return -1;
// 			}

// 			Init();

// 			windowHandle = glfwCreateWindow(this->windowWidth, this->windowHeight, this->windowTitle.c_str(), NULL, NULL);
// 			if (windowHandle == NULL) {
// 				Logger::Critical(LogChannel::Engine, "Failed to create GLFW window");
// 				glfwTerminate();
// 				return -1;
// 			}
// 			else {
// #ifndef NDEBUG
// 				Logger::Debug(LogChannel::Engine, "GLFW window created!");
// #endif // !NDEBUG
// 			}

// 			glfwMakeContextCurrent(windowHandle);
// 			if (!glfwGetCurrentContext()) {
// 				Logger::Critical(LogChannel::Engine, "Failed to make GLFW context current");
// 				return -1; 
// 			}

// 			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
// 			{
// 				Logger::Error(LogChannel::Engine, "Failed to initialize GLAD, can't continue! :(\n" + glad_glGetError());
// 				glfwTerminate();
// 			}else
// 			{
// #ifndef NDEBUG
// 				Logger::Debug(LogChannel::Engine, "GLAD initialized!");
// #endif // !NDEBUG
// 			}

// 			glViewport(0, 0, windowWidth, windowHeight);
// 			glEnable(GL_BLEND);
// 			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// 			Load();

// 			while (!glfwWindowShouldClose(windowHandle)) {
// 				Update();
// 				Render();
// 			}
			
// 			//TODO: check if window exit by user request or was forced
// #ifndef NDEBUG
// 			Logger::Debug(LogChannel::Engine, "Window has been closed.");
// #endif // !NDEBUG

// 			Unload();
// 			Shutdown();
// 			return 0;
// 		}
// 	} // namespace core
// } // namespace engine