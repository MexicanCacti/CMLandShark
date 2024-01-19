#pragma once
#ifndef STARTIMGUI_H
#define STARTIMGUI_H

#include "FileSystem.h"
#include "nfd.h"  // file explorer
#include "imgui.h"
#include "gl/glew.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <fstream>

class startImGui {
private:
  ImGuiIO io;
  Explorer Explorer;
  // Our state... add a new bool for a new window... update in Update()
  bool runProgram = true; // If true runs the main window where can select movie
  bool showFileWindow = true; // If true shows select directory window
  bool firstTime = true;  // If true will automatically display showFileWindow...otherwise will take stored directory in a text file
  bool changeDirectory = false; // If true then button to change directory was clicked

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);  // Changes background color
public:
  void Init(GLFWwindow* window, const char* glsl_version);
  void NewFrame();
  void Update();
  void Render(GLFWwindow* window);
  void ShutDown(GLFWwindow* window);
};

// Helper Functions

void displayMovies(Explorer& Explorer);  // Displays the list of movies & provides accompanying buttons


#endif