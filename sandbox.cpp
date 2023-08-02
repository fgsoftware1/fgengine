#include "pch.hpp"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Logger.hpp"
#include "IL/il.h"
#include "IL/ilu.h"
#include "Window.hpp"
#include "AssetBrowserPanel.hpp"
#include "LightComponent.hpp"
#include "CameraComponent.hpp"
#include "GL/gl.h"
#include "glm.hpp"
#include "matrix_transform.hpp"

// using editor::AssetBrowserPanel;
using engine::core::LogChannel;
using engine::core::Logger;
using engine::core::Window;

const GLint WIDTH = 800;
const GLint HEIGHT = 600;

GLuint VAO;
GLuint VBO;
GLuint FBO;
GLuint RBO;
GLuint texture_id;
GLuint shader;

std::string LoadShaderFromFile(const std::string &filePath)
{
	std::ifstream file(filePath);
	if (!file)
	{
		std::cerr << "Failed to open shader file: " << filePath << std::endl;
		return "";
	}

	std::stringstream shaderStream;
	shaderStream << file.rdbuf();
	file.close();
	return shaderStream.str();
}

unsigned int CreateShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char *vertexShaderCode = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cerr << "Vertex shader compilation failed:\n"
				  << infoLog << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fragmentShaderCode = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cerr << "Fragment shader compilation failed:\n"
				  << infoLog << std::endl;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cerr << "Shader program linking failed:\n"
				  << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

unsigned int CreateFramebufferTexture(float radius)
{
	// Create a framebuffer object (FBO)
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Create a texture to render the circle into
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// Check if the framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer is not complete!" << std::endl;
		glDeleteFramebuffers(1, &framebuffer);
		glDeleteTextures(1, &texture);
		return 0;
	}

	// Render the circle into the texture
	glViewport(0, 0, 800, 600); // Set viewport to the texture size

	// Unbind the framebuffer and texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

void RenderCircle(float radius)
{
	// Set up the vertices for the circle
	constexpr int numSegments = 60; // Number of segments for the circle
	const float angleStep = glm::radians(360.0f / static_cast<float>(numSegments));
	const float xCenter = 400.0f; // X coordinate of the circle center
	const float yCenter = 300.0f; // Y coordinate of the circle center

	float circleVertices[numSegments * 2];
	for (int i = 0; i < numSegments; ++i)
	{
		float angle = static_cast<float>(i) * angleStep;
		circleVertices[i * 2] = xCenter + radius * std::cos(angle);
		circleVertices[i * 2 + 1] = yCenter + radius * std::sin(angle);
	}

	// Create and bind a vertex array object (VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create and bind a vertex buffer object (VBO)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);

	// Set up vertex attribute pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	// Draw the circle
	glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments);

	// Cleanup
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

int main()
{
	// AssetBrowserPanel assetBrowserPanel;

	std::string vertexShaderSource = LoadShaderFromFile("assets/shaders/circle.vert");
	std::string fragmentShaderSource = LoadShaderFromFile("assets/shaders/circle.frag");

	unsigned int shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	Logger::Init();
	ilInit();
	iluInit();

	Window window = Window(1366, 768, "FGE");
	window.setVsync(true);

	ILuint image;
	ilGenImages(1, &image);
	ilBindImage(image);
	if (!ilLoadImage("assets/fge.png"))
	{
		const std::string iluErr = iluErrorString(ilGetError());
		Logger::Error(LogChannel::App, "Failed to load image: " + iluErr);
	}

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	ILubyte *imageData = ilGetData();

	GLFWimage icon;
	icon.width = width;
	icon.height = height;
	icon.pixels = imageData;
	glfwSetWindowIcon(window.getWindow(), 1, &icon);

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window.getWindow(), &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(window.getWindow());

	glViewport(0, 0, bufferWidth, bufferHeight);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	while (!glfwWindowShouldClose(window.getWindow()))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::NewFrame();
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		const ImGuiViewport *viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		ImGui::Begin("DockSpace", nullptr, window_flags);
		ImGui::PopStyleVar(2);

		ImGuiIO &io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("DockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::Begin("Hierchy", nullptr, ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
		}

		if (ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoCollapse))
		{
			const float window_width = ImGui::GetContentRegionAvail().x;
			const float window_height = ImGui::GetContentRegionAvail().y;
			glViewport(0, 0, static_cast<int>(window_width), static_cast<int>(window_height));

            unsigned int circleTexture = CreateFramebufferTexture(100.0f);

            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImGui::Image((void*)(intptr_t)circleTexture, ImVec2(window_width, window_height), ImVec2(0, 1), ImVec2(1, 0));

            glDeleteTextures(1, &circleTexture);

			RenderCircle(100.0f);

			ImGui::GetWindowDrawList()->AddImage(
				(void *)texture_id,
				ImVec2(pos.x, pos.y),
				ImVec2(pos.x + window_width, pos.y + window_height),
				ImVec2(0, 1),
				ImVec2(1, 0));
			ImGui::End();
		}

		if (ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoCollapse))
		{
			ImGui::End();
		}

		if (ImGui::Begin("BottomConatiner", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar))
		{
			if (ImGui::BeginTabBar("BottomContainer"))
			{
				// assetBrowserPanel.Render();
				if (ImGui::BeginTabItem("Log"))
				{
					{
						for (const auto &message : engine::core::Logger::s_Messages)
						{
							// TODO: check the origin console from the message
							ImGui::Text(message.second.c_str());
						}
					}
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::End();
		}

		ImGui::End();
		ImGui::Render();

		glUseProgram(shader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow *backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		window.Update();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	window.Shutdown();

	return 0;
}