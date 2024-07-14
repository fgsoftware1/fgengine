cmake_minimum_required(VERSION 3.20)
project(fge)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(WRENBIND17_BUILD_WREN ON CACHE BOOL "" FORCE)

if(MSVC)
  add_compile_options(/bigobj)
endif()

find_package(spdlog CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Stb REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(boost_algorithm REQUIRED CONFIG)
find_package(boost_filesystem REQUIRED CONFIG)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/wrenbind17)

find_path(CHAISCRIPT_INCLUDE_DIRS "chaiscript/chaiscript.hpp")

include_directories(
	${Stb_INCLUDE_DIR}
	${CHAISCRIPT_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB_RECURSE fge_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp")

add_library(${PROJECT_NAME} STATIC ${fge_SRC})
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp)
target_link_libraries(${PROJECT_NAME} PUBLIC WrenBind17 spdlog::spdlog_header_only glad::glad glfw Boost::algorithm Boost::filesystem yaml-cpp::yaml-cpp glm::glm-header-only magic_enum::magic_enum)
add_executable("Sandbox" ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox.cpp) 
target_include_directories("Sandbox" PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries("Sandbox" PRIVATE fge imgui::imgui implot::implot)
