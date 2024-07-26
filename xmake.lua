add_rules("mode.debug", "mode.release")
add_requires("spdlog", "glad", "glfw")
add_requires("imgui", {opengl3, glfw})

add_defines("GLFW_INCLUDE_NONE")

set_languages("cxx17")

if is_mode("debug")
then
    set_optimize("none")
else 
    set_optimize("fastest")
end 

target("fge")
    set_kind("static")
    add_packages("spdlog", "glad", "glfw")

target("Sandbox")
    set_kind("binary")
    add_packages("fge")
    add_files("Sandbox.cpp")
