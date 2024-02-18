cmake_minimum_required(VERSION 3.26)

project(MyProject)

set(CMAKE_CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Include directories
include_directories(include)

# Add source files
file(GLOB_RECURSE SOURCES 
    "OpenGL_startup_project/source/*.cpp"
    "OpenGL_startup_project/source/*.c"
    "OpenGL_startup_project/source/*.h"
    "OpenGL_startup_project/vendor/imgui/*.cpp"
    )

# Add executable
add_executable(OpenGL_startup_project ${SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(OpenGL_startup_project/vendor/glfw)
target_link_libraries(OpenGL_startup_project glfw)

# glad
target_include_directories(OpenGL_startup_project PRIVATE OpenGL_startup_project/vendor/glad/include)

# glm
target_include_directories(OpenGL_startup_project PRIVATE OpenGL_startup_project/vendor/glm)

# stb
target_include_directories(OpenGL_startup_project PRIVATE OpenGL_startup_project/vendor/stb)

# imgui
target_include_directories(OpenGL_startup_project PRIVATE OpenGL_startup_project/vendor/imgui)
#add_executable(OpenGL_startup_project OpenGL_startup_project/vendor/imgui/*.cpp)



set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT OpenGL_startup_project
)