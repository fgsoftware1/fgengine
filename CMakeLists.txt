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
    src/editor/include
)

set(LIBFGMATH_FILES
    src/fgmath/Vector2.cpp
    src/fgmath/Vector3.cpp 
    src/fgmath/Vector4.cpp 
    src/fgmath/Matrix4.cpp
    src/fgmath/Quaternion.cpp 
    src/fgmath/Rectangle.cpp 
    src/fgmath/AABB.cpp 
)
set(LIBFGINPUT_FILES
    src/fginput/Mouse.cpp
    src/fginput/Keyboard.cpp 
)
set(SOURCE_FILES
    #core
    src/core/InputManager.cpp
    #ecs
    #renderer
    #src/renderer/renderer.cpp
    #engine
    src/graphics/Window.cpp
    src/fgengine.cpp
)

add_library(libfgmath STATIC ${LIBFGMATH_FILES})

add_executable(fgengine 
    ${SOURCE_FILES}
)

target_link_libraries(fgengine
    ${CMAKE_SOURCE_DIR}/libs/libfgmath.lib
)