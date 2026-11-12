cmake_minimum_required(VERSION 4.3)
project(Basel_Engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# fetch glfw -------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.5.1
)

# disable un needed builds to increase compilation time
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

# fetch glad -------------------------------------------------------------------
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad
        GIT_TAG v2.0.8
        SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(glad)

glad_add_library(glad_gl TYPE STATIC API gl:core=4.6)

# fetch stb --------------------------------------------------------------------
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb
        GIT_TAG master
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(stb)

add_library(stb INTERFACE)
target_include_directories(stb SYSTEM INTERFACE ${stb_SOURCE_DIR})

# fetch glm --------------------------------------------------------------------
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.3
)

FetchContent_MakeAvailable(glm)

# fetch nlohmann/json ----------------------------------------------------------
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(json)

# fetch imgui ------------------------------------------------------------------
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG docking
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(imgui)

# if more imgui source files are needed, add here
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp

        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

# create executable and link libraries -----------------------------------------
add_executable(Basel_Engine
        src/main.cpp
        src/Window.cpp
        include/Window.hpp
        include/config.hpp
        src/Engine.cpp
        include/Engine.hpp
        src/Controller.cpp
        include/Controller.hpp
        src/Mesh.cpp
        include/Mesh.hpp
        src/Square.cpp
        include/Square.hpp
        src/Renderable.cpp
        include/Renderable.hpp
        src/Shader.cpp
        include/Shader.hpp
        src/stb_image.cpp
        include/ConfigReader.hpp
        src/Renderer.cpp
        include/Renderer.hpp
        src/Camera.cpp
        include/Camera.hpp
        src/Gui.cpp
        include/Gui.hpp
        src/Cube.cpp
        include/Cube.hpp
)

target_include_directories(Basel_Engine PRIVATE include)

target_link_libraries(Basel_Engine PRIVATE glfw glad_gl stb glm::glm OpenGL::GL imgui nlohmann_json::nlohmann_json)