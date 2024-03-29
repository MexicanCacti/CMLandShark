﻿# CMakeList.txt : CMake project for CMLandShark, include source and define
# project specific logic here.
#

# Copy the .txt file to the build directory with execute permissions
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/InitialDirectory.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add source to this project's executable.
add_executable (CMLandShark "CMLandShark.cpp" "startImGui.h" "startImGui.cpp" "FileSystem.h" "FileSystem.cpp" "CMLandShark.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMLandShark PROPERTY CXX_STANDARD 20)
endif()

find_package(GLEW REQUIRED)
target_link_libraries(CMLandShark PRIVATE GLEW::GLEW)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(CMLandShark PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(CMLandShark PRIVATE imgui::imgui)

find_package(unofficial-nativefiledialog CONFIG REQUIRED)
target_link_libraries(CMLandShark PRIVATE unofficial::nativefiledialog::nfd)

find_package(soil CONFIG REQUIRED)
target_link_libraries(CMLandShark PRIVATE soil)