#include "pch.hpp"
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Logger.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Window.hpp"
#include "LightComponent.hpp"
#include "CameraComponent.hpp"
#include "glm.hpp"

using engine::core::LogChannel;
using engine::core::Logger;
using engine::core::Window;

int main()
{
	Logger::Init();

	Window window = Window(1366, 768, "FGE");
	window.setVsync(true);

	int width, height, channels;
	unsigned char *imageData = stbi_load("assets/fge.png", &width, &height, &channels, 0);

	if (imageData == NULL)
	{
		Logger::Error(LogChannel::App, "Failed to load logo!");
	}

	GLFWimage icon;
	icon.width = width;
	icon.height = height;
	icon.pixels = imageData;
	glfwSetWindowIcon(window.getWindow(), 1, &icon);
	stbi_image_free(imageData);

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

#ifdef _WIN32
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	return main();
}

#endif //_WIN32