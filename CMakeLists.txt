# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(AlgorithmsView)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the ImGui source directory
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/libs/imgui)

# Add ImPlot source files
set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/libs/implot)
#
# set(IMPLOT_SOURCES
#     ${IMPLOT_DIR}/implot.cpp
#     ${IMPLOT_DIR}/implot_items.cpp
#     ${IMPLOT_DIR}/implot_demo.cpp
# )

# # Add ImPlot include directory
# include_directories()

# Append ImPlot sources to your build
# list(APPEND SOURCES ${IMPLOT_SOURCES})

# Add the SDL2 dependency
find_package(SDL2 REQUIRED)

# Include SDL2 and ImGui directories
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${IMPLOT_DIR}
)

# Source files for the project
set(SOURCES
    src/main.cpp
    src/app.cpp
    src/internal/logger.cpp
    src/ui/menu.cpp
    src/ui/dashboard.cpp
    src/ui/linked_list_window.cpp
    src/ui/signal_visualization_window.cpp
    src/linked_list.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
    ${IMPLOT_DIR}/implot_demo.cpp
)
# Header files for the project
set(HEADERS
    src/app.h
    src/internal/logger.h
    src/ui/menu.h
    src/ui/dashboard.h
    src/ui/linked_list_window.h
    src/ui/signal_visualization_window.h
    src/linked_list.h
)

# Verify Library Paths 
message(STATUS "Sources: ${SOURCES}")
message(STATUS "Headers: ${HEADERS}")
message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries: ${SDL2_LIBRARIES}")


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Force include <cstring> globally
target_compile_options(${PROJECT_NAME} PRIVATE -include cstring)


# Link libraries (SDL2 and OpenGL)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} GL)
# target_link_libraries(${PROJECT_NAME} implot)

