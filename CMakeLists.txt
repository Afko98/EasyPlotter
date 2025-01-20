# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(EasyPlotter)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter -Wextra -Wreorder -Wa,-mbig-obj -O2")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,67108864")

# Enable C++17 features for MSVC
if (MSVC)
    add_compile_options(/std:c++17)
endif()


# Find Boost (replace iostreams with the components you need)
find_package(Boost REQUIRED COMPONENTS iostreams)

if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost not found!")
endif()
set(BOOST_LIBRARYDIR "C:/vcpkg/installed/x64-mingw-dynamic/lib")
file(GLOB GRAPH_SOURCES Graph/*.cpp Graph/GraphTypes/*.cpp imgui/*.cpp)
file(GLOB GRAPH_HEADERS Graph/*.h Graph/GraphTypes/*.h imgui/*.h)
# Source files
set(SOURCES
    EasyPlotter.cpp
    UseImGui.cpp
    ${GRAPH_SOURCES}
    imgui/ImGuiFileDialog/ImGuiFileDialog.cpp
    imgui/backends/imgui_impl_dx9.cpp
    imgui/backends/imgui_impl_win32.cpp
)

# Header files (optional, but good practice for IDEs)
set(HEADERS
    exprtk/exprtk.hpp
    ${GRAPH_HEADERS}
    imgui/ImGuiFileDialog/ImGuiFileDialog.h
    imgui/backends/imgui_impl_dx9.h
    imgui/backends/imgui_impl_win32.h
)



# Include directories
include_directories(${CMAKE_SOURCE_DIR}/exprtk)
include_directories(${CMAKE_SOURCE_DIR}/imgui)
include_directories(${CMAKE_SOURCE_DIR}/imgui/backends)
include_directories(${CMAKE_SOURCE_DIR}/Graph)
include_directories(${CMAKE_SOURCE_DIR}/Graph/GraphTypes)
include_directories(${CMAKE_SOURCE_DIR}/imgui/ImGuiFileDialog)

# Header files: Automatically include all .h/.hpp files in your project (optional)
file(GLOB_RECURSE HEADERS
    ${CMAKE_SOURCE_DIR}/*.h
    ${CMAKE_SOURCE_DIR}/*.hpp
)
# Create the executable
add_executable(EasyPlotter ${SOURCES} ${HEADERS})

# Link Boost and other libraries
target_link_libraries(EasyPlotter ${Boost_LIBRARIES} d3d9 dinput8 user32 gdi32 Dwmapi)