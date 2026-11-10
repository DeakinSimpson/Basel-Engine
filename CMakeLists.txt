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

# fetch glad -------------------------------------------------------------------
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad
        GIT_TAG v2.0.8
        SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(glad)

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

glad_add_library(glad_gl TYPE STATIC API gl:core=4.6)

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
        src/Cube.cpp
        include/Cube.hpp
        src/Renderable.cpp
        include/Renderable.hpp
        src/Shader.cpp
        include/Shader.hpp
        src/stb_image.cpp
)

target_include_directories(Basel_Engine PRIVATE include)

find_package(OpenGL REQUIRED)
target_link_libraries(Basel_Engine PRIVATE glfw glad_gl stb glm::glm OpenGL::GL nlohmann_json::nlohmann_json)