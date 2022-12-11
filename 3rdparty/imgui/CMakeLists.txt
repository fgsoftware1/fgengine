cmake_minimum_required (VERSION 3.8)
cmake_policy(SET CMP0072 NEW)

project (libimgui LANGUAGES CXX VERSION 0.1)

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
    .
)

set(SOURCE_FILES
    imgui_draw.cpp 
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp   
)

add_library(libimgui STATIC ${SOURCE_FILES})
