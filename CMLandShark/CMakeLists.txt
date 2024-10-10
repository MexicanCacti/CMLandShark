# CMakeList.txt : CMake project for CMLandSharkChild, include source and define
# project specific logic here.
#
project("CMLandShark")

# Copy the .txt file to the build directory with execute permissions
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/InitialDirectory.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add source to this project's executable.
add_executable (CMLandShark "CMLandShark.cpp" "startImGui.h" "startImGui.cpp" "FileSystem.h" "FileSystem.cpp" "CMLandShark.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMLandShark PROPERTY CXX_STANDARD 20)
endif()

# Set the CMAKE_PREFIX_PATH to include vcpkg_installed directory
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows" ${CMAKE_PREFIX_PATH})

# set CMAKE_INCLUDE_PATH and CMAKE_LIBRARY_PATH if needed
set(CMAKE_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/include" ${CMAKE_INCLUDE_PATH})
set(CMAKE_LIBRARY_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-windows/lib" ${CMAKE_LIBRARY_PATH})

find_package(GLEW REQUIRED)
target_link_libraries(CMLandShark PRIVATE GLEW::GLEW)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(CMLandShark PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(CMLandShark PRIVATE imgui::imgui)

find_package(soil CONFIG REQUIRED)
target_link_libraries(CMLandShark PRIVATE soil)

target_link_libraries(CMLandShark PRIVATE nfd)

