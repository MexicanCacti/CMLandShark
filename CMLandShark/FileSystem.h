#pragma once
#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#ifdef _WIN32
  // Window Specific
  #include <windows.h>
#else
  // Linux/Unix
  #include <dirent.h>
  #include <sys/stat.h>
  #include <cstring>
#endif
#include <string>
#include <vector>
struct Image {
  std::string imagePath;  // Path to image... EX: C:\Directory\mediaFolder\Image.png
  float hSize;            // Height of image
  float wSize;            // Width of image
  void inline setImageSize(const float height, const float width) { hSize = height, wSize = width; }
};

struct Media {
  std::string mediaName;  // Name of mediaFolder containing files
  std::string mediaPath;  // Path to media... EX: C:\Directory\mediaFolder\movie.mp4
  Image image;
};

class Explorer {
private:
  std::string DirectoryPath;  // Path to directory containing all media EX: C:\Directory
  std::vector<Media>Medias;   // Every folder creates a media object which is stored in a list
  // Media Dummy;
public:
  // Helper Functions to search through directory
  friend void getFolders(Explorer& Explorer);
  friend Media getFiles(const std::string& folderName, Explorer& Explorer);

  inline void setDirectoryPath(std::string dPath) { DirectoryPath = dPath; clearMedia(); findMedia(); } // Sets path to directory & Clears existing list of Media objects & Creates new list
  inline std::string getDirectoryPath() { return DirectoryPath; }  // Gets path to directory
  inline void findMedia() { getFolders(*this); }  // Searches through list of folders in directory to create list of Media objects
  inline bool isMissing() { return DirectoryPath.empty(); }  // Checks if there is a stored directory path. True = Not Stored || False = Stored
  inline void clearMedia() { Medias.clear(); } // Clears list of stored Media objects.

  std::string const getMedia(const std::string MediaName);  // Gets path to MediaName by name
  std::string const getMedia(const int index);  // Gets path to MediaName by index
  std::string getImage(const std::string MediaName);  // Gets path to MediaName's image by name
  std::string getImage(const int index);  // Gets path to MediaName's image by index
  inline std::vector<Media> getMedias() { return Medias; } // Gets list of Media objects
};

// Create default image


#endif