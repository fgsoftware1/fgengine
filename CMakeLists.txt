cmake_minimum_required (VERSION 3.8)
cmake_policy(SET CMP0072 NEW)

project (fgengine LANGUAGES CXX VERSION 0.1)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -ldl -lpthread -lm")
endif()
set(CMAKE_CXX_STANDARD 20)

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_compile_definitions(DEBUG_BUILD)
else()
    add_compile_definitions(RELEASE_BUILD)
endif()

include_directories(
    src/include
)

set(LIBFGUTILS_FILES
    src/utils/FileManager.cpp
)
set(SOURCE_FILES
    #core
    src/core/InputManager.cpp
    #renderer
    src/renderer/OpenGL/Shader.cpp
    #engine
    src/fgengine.cpp
    #editor
    src/editor/fgeditor.cpp
)

add_library(libfgutils STATIC ${LIBFGUTILS_FILES})

add_executable(fgengine 
    ${SOURCE_FILES}
)

add_custom_command(TARGET fgengine
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/assets/shader.vs ${PROJECT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/assets/shader.fs ${PROJECT_BINARY_DIR}
)

target_compile_definitions(fgengine PUBLIC 
    GLEW_STATIC 
    IMGUI_IMPL_OPENGL_LOADER_GLEW
)
target_link_libraries(fgengine
    ${CMAKE_SOURCE_DIR}/libs/libglew.lib
    ${CMAKE_SOURCE_DIR}/libs/libimgui.lib
    ${CMAKE_SOURCE_DIR}/libs/libfgmath.lib
    ${CMAKE_SOURCE_DIR}/libs/libfgutils.lib
)