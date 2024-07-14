#define STB_IMAGE_IMPLEMENTATION

#include <windows.h>
#include <psapi.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "implot.h"
#include "boost/filesystem.hpp"
#include "stb_image.h"

#include "core/GameWindow.hpp"
#include "assets/ResourceManager.hpp"
#include "assets/Project.hpp"
#include "ecs/EntityFactory.hpp"
#include "ecs/Entity.hpp"
#include "ecs/components/Transform.hpp"
#include "ecs/components/ScriptComponent.hpp"
#include "ecs/components/SpriteRenderer.hpp"

using namespace engine::core;

bool isAssetBrowserInitialized = false;
boost::filesystem::path currentPath;
Ref<Entity> Entity::selectedEntity = nullptr;
// TEMP
Ref<Entity> root = CreateRef<Entity>("Root");
Ref<Entity> child1 = CreateRef<Entity>("Child 1");

GLuint folderTex;
GLuint fileTex;
GLuint cmakeTex;
GLuint cppTex;
GLuint wrenTex;
GLuint chaiTex;
SpriteRenderer *Renderer;

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

enum class ItemType
{
	File,
	Folder
};

void drawAssetBrowser(const boost::filesystem::path &projectPath);
void drawItem(const boost::filesystem::path &path);

void createScript(const std::string &projectName, const std::string &scriptName)
{
	boost::filesystem::path scriptPath = "./" + projectName + "/Assets/Scripts/" + scriptName + ".cpp";

	if (boost::filesystem::exists(scriptPath))
	{
		Logger::Info(LogChannel::App, "A script with the name " + scriptName + " already exists.\n");
		return;
	}

	std::ofstream file(scriptPath.string());

	file << "#pragma once\n";
	file << "\n";
	file << "#include <Script.hpp>\n";
	file << "\n";
	file << "class " << scriptName << " : public Script {\n";
	file << "public:\n";
	file << "    void start() override {\n";
	file << "        // Initialization code here\n";
	file << "    }\n\n";
	file << "    void update() override {\n";
	file << "        // Game logic here\n";
	file << "    }\n\n";
	file << "    void destroy() override {\n";
	file << "        // Cleanup code here\n";
	file << "    }\n";
	file << "};\n";

	file.close();
	drawAssetBrowser(currentPath);
}

ItemType getItemType(const boost::filesystem::path &path)
{
	if (boost::filesystem::is_directory(path))
	{
		return ItemType::Folder;
	}
	else
	{
		return ItemType::File;
	}
}

static GLuint loadTexture(const char *filename)
{
	int width, height, channels;
	unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
	if (!data)
	{
		std::cerr << "Failed to load image: " << filename << "\n";
		return 0;
	}
	if (data)
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
		return texture;
	}
	else
	{
		std::cout << "Failed to load image: " << filename << "\n";
		return 0;
	}
}

void drawAssetBrowser(const boost::filesystem::path &projectPath)
{
	try
	{
		ImGui::Columns(8, "mycolumns");
		for (const auto &entry : boost::filesystem::directory_iterator(projectPath))
		{
			drawItem(entry.path());
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
	}
	catch (const boost::filesystem::filesystem_error &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}
}

void drawItem(const boost::filesystem::path &path)
{
	int counter = 0;
	ItemType type = getItemType(path);
	std::string name = path.stem().string();

	if (type == ItemType::Folder)
	{
		if (ImGui::ImageButton((void *)(intptr_t)folderTex, ImVec2(64, 64)))
		{
			currentPath = path;
			drawAssetBrowser(currentPath);
		}

		ImGui::Text("%s", name.c_str());
	}
	else if (type == ItemType::File)
	{
		std::string extension = path.extension().string();
		if (extension == ".cpp")
		{
			if (ImGui::ImageButton((void *)(intptr_t)cppTex, ImVec2(64, 64)))
			{
				std::string command = "start devenv " + path.string();
				system(command.c_str());
			}
		}
		else if (extension == ".wren")
		{
			if (ImGui::ImageButton((void *)(intptr_t)wrenTex, ImVec2(64, 64)))
			{
				std::string command = "start devenv " + path.string();
				system(command.c_str());
			}
		}
		else if (extension == ".chai")
		{
			if (ImGui::ImageButton((void *)(intptr_t)chaiTex, ImVec2(64, 64)))
			{
				std::string command = "start devenv " + path.string();
				system(command.c_str());
			}
		}
		else if (name == "CMakeLists")
		{
			if (ImGui::ImageButton((void *)(intptr_t)cmakeTex, ImVec2(64, 64)))
			{
				std::string command = "start devenv " + path.string();
				system(command.c_str());
			}
		}
		else
		{
			ImGui::Image((void *)(intptr_t)fileTex, ImVec2(64, 64));
		}

		ImGui::Text("%s", name.c_str());
	}
}

void GameWindow::Init()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void GameWindow::Load()
{
	glfwSetFramebufferSizeCallback(this->windowHandle, FramebufferSizeCallback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(this->windowHandle, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	folderTex = loadTexture("assets/folder.png");
	fileTex = loadTexture("assets/file.png");
	cmakeTex = loadTexture("assets/cmake.png");
	cppTex = loadTexture("assets/cpp.png");
	wrenTex = loadTexture("assets/wren.png");
	chaiTex = loadTexture("assets/chai.png");

	// TEMP
	root->addComponent<Transform>("Transform", new Transform(0.0f, 0.0f, 0.0f));
	child1->addComponent<Transform>("Transform", new Transform(1.0f, 0.0f, 0.0f));
	child1->addComponent<ScriptComponent>("Script", new ScriptComponent("file.cpp"));

	root->addChild(child1);

	// load shaders
	ResourceManager::LoadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", nullptr, "sprite");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->windowWidth), static_cast<float>(this->windowHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// load textures
	ResourceManager::LoadTexture("assets/textures/awesomeface.png", true, "face");
}

void GameWindow::Update()
{
}

void GameWindow::Render()
{
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	const ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImVec4 clear_color = ImColor(114, 144, 154);
	// TEMP
	Project project = Project("TestCmakeProject");

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui::NewFrame();

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
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Create empty object"))
			{
				root->addChild(EntityFactory::createEmptyObject());
			}
			if (ImGui::BeginMenu("2D Object"))
			{
				if (ImGui::BeginMenu("Sprites"))
				{
					if (ImGui::MenuItem("Circle"))
					{
						b2Vec2 gravity(0.0f, -9.8f);
						b2World *world = new b2World(gravity);
						root->addChild(EntityFactory::createCircle(world));
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}
		root->drawEntities(root);

		ImGui::End();
	}

	if (ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoCollapse))
	{
		Texture2D texture = ResourceManager::GetTexture("face");

		float aspectRatio = (float)texture.Width / (float)texture.Height;
		float newWidth = 300.0f;
		float newHeight = newWidth / aspectRatio;

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 pos = ImVec2((windowSize.x - newWidth) * 0.5f, (windowSize.y - newHeight) * 0.5f);

		Renderer->DrawSprite(texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

		ImGui::SetCursorPos(pos);
		ImGui::Image((void *)(intptr_t)texture.ID, ImVec2(newWidth, newHeight));
		ImGui::End();
	}

	if (ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoCollapse))
	{
		Ref<Entity> selectedEntity = Entity::getSelectedEntity();
		if (selectedEntity)
		{
			selectedEntity->drawComponents();

			// Calculate the position to center the button text
			float buttonWidth = ImGui::CalcTextSize("Add Component").x;
			float centerPos = (ImGui::GetContentRegionAvail().x - buttonWidth) / 2.0f;

			ImGui::SetCursorPosX(centerPos);

			if (ImGui::Button("Add Component", ImVec2(-1, 0))) // Button width will span the entire window width
			{
				ImGui::OpenPopup("Add Component Modal");
			}
		}

		if (ImGui::BeginPopupModal("Add Component Modal", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			static char searchBuffer[128] = "";

			std::vector<std::string> allComponents = Component::getComponentNames();
			std::vector<std::string> entityComponents = selectedEntity->getComponentNames();

			ImGui::InputText("Search", searchBuffer, IM_ARRAYSIZE(searchBuffer));

			if (ImGui::BeginCombo("Components", ""))
			{
				for (const auto &component : allComponents)
				{
					bool isAlreadyAdded = (std::find(entityComponents.begin(), entityComponents.end(), component) != entityComponents.end());
					if (!isAlreadyAdded || component == "Script")
					{
						if (ImGui::Selectable(component.c_str()))
						{
							selectedEntity->addComponentByName(component);
						}
					}
				}
				ImGui::EndCombo();
			}

			if (ImGui::Button("OK", ImVec2(120, 0)))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::EndPopup();
		}

		ImGui::End();
	}

	if (ImGui::Begin("BottomConatiner", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar))
	{
		if (ImGui::BeginTabBar("BottomContainer"))
		{
			if (ImGui::BeginTabItem("AssetBrowser"))
			{
				static char scriptName[32] = "";

				if (ImGui::MenuItem("Create C++ Script"))
				{
					// Set the initial script name
					strcpy(scriptName, "NewScript");

					// Open a new ImGui window to prompt for the script name
					ImGui::OpenPopup("Create Script");
				}

				// Modal window to enter script name
				if (ImGui::BeginPopupModal("Create Script", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Enter script name:");
					ImGui::Separator();

					// Input text field for the script name
					ImGui::InputText("##scriptname", scriptName, IM_ARRAYSIZE(scriptName));

					// Create the script if the "OK" button is pressed
					if (ImGui::Button("OK", ImVec2(120, 0)))
					{
						createScript(project.getProjectPath(), scriptName);
						ImGui::CloseCurrentPopup();
					}

					ImGui::SameLine();
					if (ImGui::Button("Cancel", ImVec2(120, 0)))
					{
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				if (!isAssetBrowserInitialized)
				{
					currentPath = project.getProjectPath();
					isAssetBrowserInitialized = true;
				}

				drawAssetBrowser(currentPath);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Log"))
			{
				for (const auto &message : engine::core::Logger::s_Messages)
				{
					// TODO: check the origin console from the message
					ImGui::Text(message.second.c_str());
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
	glfwSwapBuffers(this->windowHandle);
	glfwPollEvents();
}

void GameWindow::Unload()
{
	// Destroy imgui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GameWindow::Shutdown()
{
	// Destroy GLFW
	glfwDestroyWindow(this->windowHandle);
	glfwTerminate();
}