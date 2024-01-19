#include "startImGui.h"

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

  return;
}
// NOTE: you DONT have to call this for every new window, just the once
void startImGui::NewFrame() {
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  return;
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
      ImGui::Begin("Select Directory", &showFileWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
      ImGui::SetWindowPos(ImVec2(100, 100));  // Window position
      ImGui::SetWindowSize(ImVec2(800, 800)); // Window size
      ImGui::Text("Find Main Movie Directory: ");
      if (ImGui::Button("SelectFolder")) {
        out.open("InitialDirectory.txt");
        nfdchar_t* outPath = nullptr;
        nfdresult_t result = NFD_PickFolder(nullptr, &outPath);
        
        if (result == NFD_OKAY) {
          Explorer.setDirectoryPath(outPath);
          Explorer.findMedia();
          out << Explorer.getDirectoryPath();
          showFileWindow = false;
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
    ImGui::End();
  };
    
    ImGui::Text("Current directory: %s", Explorer.getDirectoryPath().c_str());
    displayMovies(Explorer);
    if (ImGui::Button("Change Directory")) {
      showFileWindow = true;
    }
    ImGui::End();
  }

  return;
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