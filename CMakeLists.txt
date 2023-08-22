cmake_minimum_required(VERSION 3.25)
project(FGE LANGUAGES CXX C)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/devil/DevIL/src-IL)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/devil/DevIL/src-ILU)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	add_compile_options(-g)
endif()

include_directories(
	#ROOT
	${CMAKE_CURRENT_SOURCE_DIR}
	#VENDOR
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/filewatch
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/glm/gtc
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/devil/DevIL/include
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw/include
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb/include
	#ENGINE
	${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/core
	${CMAKE_CURRENT_SOURCE_DIR}/src/engine/renderer
	${CMAKE_CURRENT_SOURCE_DIR}/src/engine/renderer/openGL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/components
	#EDITOR
	${CMAKE_CURRENT_SOURCE_DIR}/src/editor/panels
)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/mono)

file(GLOB_RECURSE IMGUI_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_tables.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp
)
file(GLOB_RECURSE ENGINE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/core/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/engine/renderer/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/engine/renderer/openGL/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ecs/components/*.cpp
)
file(GLOB_RECURSE EDITOR_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/editor/panels/*.cpp
)

add_library(glad STATIC vendor/glad/src/glad.c)
add_library(imgui STATIC ${IMGUI_SRC})
add_library(engine STATIC ${ENGINE_SRC})

target_precompile_headers(engine PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/utils.hpp
)
target_link_libraries(engine PRIVATE
	spdlog
	glm
	glad
	IL
	ILU
	glfw
	imgui
)

add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox
	engine
)

add_custom_target(Copyfiles ALL
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sandbox> ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:IL> ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ILU> ${CMAKE_CURRENT_SOURCE_DIR}/dist
	#COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:spdlog> ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glfw> ${CMAKE_CURRENT_SOURCE_DIR}/dist
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_SOURCE_DIR}/dist/assets
    COMMENT Copying files...
)