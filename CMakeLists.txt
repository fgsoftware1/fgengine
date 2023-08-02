cmake_minimum_required(VERSION 3.25)
project(FGE LANGUAGES CXX C)

add_subdirectory(vendor/glm)

add_definitions(-DFMT_HEADER_ONLY)
add_compile_options(-fPIC)

if(UNIX)
	find_package(OpenGL REQUIRED)
	find_package(DevIL REQUIRED)
	include_directories(
		${OPENGL_INCLUDE_DIR}
		"/usr/include/spdlog"
	)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_compile_options(-g)
endif()

include_directories(
	#ROOT
	${CMAKE_CURRENT_SOURCE_DIR}
	#VENDOR
	"vendor/glad/include"
	"vendor/imgui"
	"vendor/imgui/backends"
	"vendor/filewatch"
	"vendor/glm/glm"
	"vendor/glm/glm/gtc"
	#ENGINE
	"src/engine"
    "src/engine/core"
	"src/engine/renderer"
	"src/engine/renderer/openGL"
    "src/engine/ecs"
    "src/engine/ecs/components"
	#EDITOR
	"src/editor/panels"
)

file(GLOB_RECURSE IMGUI_SRC
    "vendor/imgui/imgui.cpp"
    "vendor/imgui/imgui_draw.cpp"
    "vendor/imgui/imgui_tables.cpp"
	"vendor/imgui/imgui_widgets.cpp"
	"vendor/imgui/backends/imgui_impl_opengl3.cpp"
	"vendor/imgui/backends/imgui_impl_glfw.cpp"
)
file(GLOB_RECURSE ENGINE_SRC
    "src/engine/core/*.cpp"
    "src/engine/ecs/*.cpp"
	"src/engine/renderer/*.cpp"
	"src/engine/renderer/openGL/*.cpp"
    "src/engine/ecs/components/*.cpp"
)
file(GLOB_RECURSE EDITOR_SRC
	"src/editor/panels/*.cpp"
)

add_library(glad STATIC vendor/glad/src/glad.c)
add_library(imgui STATIC ${IMGUI_SRC})
add_library(engine STATIC ${ENGINE_SRC})
add_library(editor STATIC ${EDITOR_SRC})
target_precompile_headers(engine PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp
)
target_link_libraries(engine PRIVATE
	GL
	glm
	glad
	glfw
	IL
	ILU
	imgui
	spdlog
)
target_link_libraries(editor PRIVATE
	imgui
	engine
)

add_executable(sandbox "sandbox.cpp")
target_link_libraries(sandbox
	editor
)

add_custom_target(CopyFiles ALL
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sandbox> ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_SOURCE_DIR}/dist/assets
    COMMENT "Copying files..."
)