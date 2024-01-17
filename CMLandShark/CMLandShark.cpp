// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp
#define STB_IMAGE_IMPLEMENTATION
//#include <GL/glew.h>    // inclde glew
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include "Explorer.h" // media explorer (saves directory & file with in)
#include <fstream> // read/write files
#include <nfd.h> // file explorer
#include <iostream> // DELTE ME
// [Win32] Example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    // HSize = 1280, WSize = 720
    GLFWwindow* window = glfwCreateWindow(1280, 720, "LandShark", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    /*
    // Initialize GLEW after creating the OpenGL context
    if (glewInit() != GLEW_OK) {
      fprintf(stderr, "Failed to initialize GLEW\n");
      return -1;
    }  
    */

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool runProgram = true; // if true runs the main window where can select movie
    bool showFileWindow = true; // if true shows select directory window
    bool firstTime = true;  // if true will automatically display showFileWindow...otherwise will take stored directory in a text file
    bool changeDirectory = false; // if true then button to change directory was clicked
    Explorer Explore;  // our main object to store info
    std::string inputString;
    std::ofstream out;
    std::ifstream in;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Forward declarations of helper functions
    void displayMovies(Explorer Explore, std::string Directory);  // displays list of movies as buttons
    //void playMovie(const std::string& moviePath);

    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        //CODE START HERE!
        
        if (runProgram) {
          ImGui::Begin("LandShark", &runProgram);
          // if first time opening program automatically checks text file for directory
          if (firstTime) {
            in.open("Initial Directory.txt");
            std::getline(in, inputString);
            Explore.setDirectoryPath(inputString);
            in.close();
            firstTime = false;
            // if we already have a saved directory dont bother opening window to select a new directory
            if (!Explore.isMissing()) {
              showFileWindow = false;
            }
            else {
              Explore.findMedia(); // store a vector of movie objects. movies objects have folder name, media path, image path
            }
          }
          else {
            Explore.clearMedia();
            Explore.findMedia();
          }
          // this window is for selecting the main movie directory
          // TODO: Parse through the files in the directory & put .mp4/.mkv/movies + image into a list of objects
          if (showFileWindow) {

            ImGui::Begin("Inital Start Up", &showFileWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
            ImGui::SetWindowPos(ImVec2(100, 100));
            ImGui::SetWindowSize(ImVec2(800, 800));
            // opens window to select main movie directory... outfile to put directory path in text file
            if (Explore.isMissing() || changeDirectory) {
              out.open("Initial Directory.txt");
              ImGui::Text("Find Main Movie Directory: ");
              // open file explorer to select main movie directory
              if (ImGui::Button("SelectFolder")) {
                nfdchar_t* outPath = nullptr;
                nfdresult_t result = NFD_PickFolder(nullptr, &outPath);

                if (result == NFD_OKAY) {
                  Explore.setDirectoryPath(outPath);
                  Explore.clearMedia();
                  Explore.findMedia();
                  out << Explore.getDirectoryPath();
                  showFileWindow = false;
                  changeDirectory = true;
                }
                else if (result == NFD_CANCEL) {
                  ImGui::Text("Canceled Selection");
                }
                else {
                  ImGui::Text("Error Opening File Dialog");
                }
              }
              if (ImGui::Button("Close")) {
                showFileWindow = false;
              }
            }
            out.close();
            ImGui::End();
          };

          ImGui::Text("This is the directory: %s", Explore.getDirectoryPath().c_str());
          displayMovies(Explore, Explore.getDirectoryPath());
          if (ImGui::Button("Change Directory")) {
            showFileWindow = true;
            changeDirectory = true;
          }
          ImGui::NewLine();
          if (ImGui::Button("Exit")) {
            runProgram = false;
          }
          ImGui::End();
        };

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

// Helper functions
void displayMovies(Explorer Explore, std::string DirectoryPath) {
  ImGui::NewLine();
  // used to keep track when to go to the next line
  float maxLineWidth = ImGui::GetWindowWidth() / 1.5;

  // dimensions for the button. Eventually base on window size?
  float maxButtonWidth = maxLineWidth / 5.0; // MAX: 5 movies per line

  float maxButtonHeight = 100.0f;
  // get the size of the window to use to decide when to go the the next line of movie display
  ImVec2 windowSize = ImGui::GetWindowSize();
  float currentLineWidth = 0.0f;
  for (int i = 0; i < Explore.getAmount(); i++) {
    // make it so it is an image button
    // get the path to the image
    std::string imagePath = DirectoryPath + "\\" + Explore.getMedia(i).mediaName + "\\" + Explore.getImage(i).imagePath;
    Explore.getImage(i).setImageSize(maxButtonHeight, maxButtonWidth);
    // load image
    const char* imageName = imagePath.c_str();
    int width = static_cast<int>(std::ceilf(Explore.getImage(i).wSize));
    int height = static_cast<int>(std::ceilf(Explore.getImage(i).hSize));
    int channels = 3; // 3 for rgb 
    // create button with image (Vec2 determines height & width)
    unsigned char* image = stbi_load(imageName, &width, &height, &channels, 3);
    //CHANGE THIS EVENTUALLY
    GLuint Texture;
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    
    // create texture ID from loaded image... maybe put a check to see if successfully loaded?
    // load the images at the beginning of the program? Maybe in Explorer FindMedia?
    if (ImGui::ImageButton((ImTextureID)image, ImVec2(Explore.getImage(i).wSize, Explore.getImage(i).hSize))) {
      // if click open media player using mediapath
      std::string moviePath = DirectoryPath + "\\" + Explore.getMedia(i).mediaName + "\\" + Explore.getMedia(i).mediaPath;
      //playMovie(moviePath);
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