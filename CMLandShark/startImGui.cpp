#include "startImGui.h"

#include <iostream>
// so in init maybe check if have working directory files? if so then load the images?
void startImGui::Init(GLFWwindow* window, const char* glsl_version) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight(); //if you want light mode
}

// NOTE: you DONT have to call this for every new window, just the once
void startImGui::NewFrame() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

// so for adding new windows and the such put them in here!
void startImGui::Update() {
  std::string inputString;
  std::ifstream in;
  std::ofstream out;
  if (runProgram) {
    ImGui::Begin("CMLandShark", &runProgram);
    // If it is the first time opening the program, auto checks InitalDirectory.txt for Directory
    if (firstTime) {
      in.open("InitialDirectory.txt");
      if (in.is_open()) {
        std::getline(in, inputString);
        Explorer.setDirectoryPath(inputString);
        in.close();
      }
      firstTime = false;
      if (!Explorer.isMissing()) {  // Found a directory don't auto-open directory selection window
        showFileWindow = false;
      }
      else {
        Explorer.findMedia();
      }
    }
    // Window for selecting main movie directory
    if (showFileWindow) {
      if(NFD_Init() != NFD_OKAY) {
        std::cout << NFD_GetError() << std::endl;
      }
      ImGui::Begin("Select Directory", &showFileWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
      ImGui::SetWindowPos(ImVec2(100, 100));  // Window position
      ImGui::SetWindowSize(ImVec2(800, 800)); // Window size
      ImGui::Text("Find Main Movie Directory: ");
      if (ImGui::Button("SelectFolder")) {
        out.open("InitialDirectory.txt");
        nfdu8char_t * outPath = nullptr;
        nfdresult_t result = NFD_PickFolderU8(&outPath, nullptr);
        
        if (result == NFD_OKAY) {
          Explorer.setDirectoryPath(outPath);
          Explorer.findMedia();
          out << Explorer.getDirectoryPath();
          showFileWindow = false;
          NFD_FreePathU8(outPath);
        }
        else if (result == NFD_CANCEL) {             
          ImGui::Text("Canceled Selection");
        }
        else {
          ImGui::Text("Error Opening File Dialog");
        }
        out.close();
      }
      if (ImGui::Button("Close")) {
        showFileWindow = false;
      }
      NFD_Quit();
      ImGui::End();
    }

    ImGui::Text("Current directory: %s", Explorer.getDirectoryPath().c_str());
    displayMovies(Explorer);
    if (ImGui::Button("Change Directory")) {
      showFileWindow = true;
    }
    ImGui::End();
  }
}

void startImGui::Render(GLFWwindow* window) {
  ImGui::Render();
  int display_w, display_h;
  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(window);
  return;
}

void startImGui::ShutDown(GLFWwindow* window) {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  return;
}

void displayMovies(Explorer& Explorer) {
  std::string imagePath;
  const char* imageName;
  int i_Width, i_Height;
  unsigned char* image;
  GLuint Texture;


  ImGui::NewLine();
  
  float maxLineWidth = ImGui::GetWindowWidth() / 1.5; // Keep track when to go to next line
  
  // Dimensions for buttons
  float maxButtonWidth = maxLineWidth / 5.0f;
  float maxButtonHeight = 100.0f;  
  
  ImVec2 windowSize = ImGui::GetWindowSize(); // Get size of window to help deciding when to go to next line
  float currentLineWidth = 0.0f;
  for (const auto& movie : Explorer.getMedias()) {
    imagePath = movie.image.imagePath.c_str();
    if (ImGui::Button(movie.mediaName.c_str())) {
      playMovie(movie.mediaPath);
    }
    currentLineWidth += ImGui::GetItemRectSize().x + ImGui::GetStyle().ItemSpacing.x;
    if (currentLineWidth > maxLineWidth) {
      ImGui::NewLine();
      currentLineWidth = 0.0f;
    }
    else {
      ImGui::SameLine();
    }
  }
  ImGui::NewLine();
  ImGui::NewLine();
}

void playMovie(const std::string& moviePath) {
#ifdef _WIN32
  HINSTANCE result = ShellExecute(NULL, "open", moviePath.c_str(), NULL, NULL, SW_SHOWNORMAL);

  if((intptr_t)result <= 32) {
    MessageBox(NULL, ("Error opening movie file with path: " + moviePath + "!").c_str(), "Error", MB_OK | MB_ICONERROR);
  }
#else
  std::string command = "xdg-open \"" + moviePath + "\"";
  int result = std::system(command.c_str());
  if (result == 0) {
    std::cerr << "Error opening movie file with path: " << moviePath << "!" << std::endl;
  }
#endif
}
