#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "pch.hpp"
#include "math/Matrix4x4.hpp"

// Forward declaration
class Entity;

// Component class
class Component {
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
};

// Entity class
class Entity {
public:
    std::vector<Ref<Component>> components;

    void update() {
        for (auto component : components) {
            component->update();
        }
    }

    void draw() {
        for (auto component : components) {
            component->draw();
        }
    }

    template <typename T>
    Ref<T> addComponent() {
        Ref<T> newComponent = CreateRef<T>();
        newComponent->entity = this;
        components.push_back(newComponent);
        newComponent->init();
        return newComponent;
    }
};

// System class
class System {
public:
    virtual void update(Entity* entity) {}
    virtual void draw(Entity* entity) {}
};

// Global variables for selected entity and its components
Entity* selectedEntity = nullptr;
std::vector<Ref<Component>> selectedComponents;

// Function to display the entity tree
void DisplayEntityTree(Entity* entity) {
    if (ImGui::TreeNode(entity, "Entity")) {
        if (ImGui::IsItemClicked()) {
            selectedEntity = entity;
            selectedComponents = entity->components;
        }

        for (auto& component : entity->components) {
            ImGui::BulletText("Component");
        }

        ImGui::TreePop();
    }
}

int main() {
    Matrix4x4 matrix;
    std::cout << matrix;  // Print the initial matrix

    std::cout << Matrix4x4::Identity;  // Print the identity matrix
    std::cout << Matrix4x4::Zero;  // Print the zero matrix

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a window with GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Window", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup platform/renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Create entities
    Entity player;
    Entity enemy;

    // Add components to entities
    player.addComponent<Component>();
    enemy.addComponent<Component>();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Display entity tree
        if (ImGui::TreeNode("Entity Tree")) {
            DisplayEntityTree(&player);
            DisplayEntityTree(&enemy);
            ImGui::TreePop();
        }

        // Display selected entity components
        if (selectedEntity) {
            if (ImGui::TreeNode("Selected Entity")) {
                for (auto& component : selectedComponents) {
                    ImGui::BulletText("Component");
                }
                ImGui::TreePop();
            }
        }

        // Render ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}