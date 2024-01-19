#pragma once
#include <string>
#include <vector>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING //allows the use of filesystem to get directory path
#include <experimental/filesystem> 
namespace fs = std::experimental::filesystem;
#include <SOIL/SOIL.h>
struct Image {
  std::string imagePath;
  float hSize = 256.0;  // height of the button (height of the image)
  float wSize = 256.0;  // width of the button (width of the image)
  void inline setImageSize(const float height, const float width) {hSize = height, wSize = width; }
};

// can add other attributes here eventually... like maybe a std::string for description that takes a textfile?
struct Media {
  std::string mediaName;
  std::string mediaPath;
  Image image;
};


void getFolders(std::vector<Media>& Medias, std::string Directory);

Media getFiles(std::string Folder, std::string Directory);

std::string createDefaultImage(std::string Path);