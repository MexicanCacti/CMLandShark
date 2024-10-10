#include "FileSystem.h"

#include <iostream>

void getFolders(Explorer& Explorer) {
#ifdef _WIN32
  WIN32_FIND_DATA findFolders;
  HANDLE folderFind = FindFirstFile((Explorer.getDirectoryPath() + "\\*").c_str(), &findFolders);

  if(folderFind != INVALID_HANDLE_VALUE) {
    while(FindNextFile(folderFind, &findFolders) != 0) {
      std::string fileName = findFolders.cFileName;
      if(findFolders.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        // It's a folder
        if(fileName != "." && fileName != "..") {
          Media media = getFiles(fileName, Explorer);
          if(!media.mediaPath.empty()) Explorer.Medias.push_back(media);
        }
      }
    }
  }
  FindClose(folderFind);
#else
  DIR* dir = opendir(Explorer.getDirectoryPath().c_str());
  if (dir == nullptr) {
    return;
  }

  struct dirent* entry;
  while ((entry = readdir(dir)) != nullptr) {
    std::string fileName = entry->d_name;
    struct stat info;
    std::string fullPath = Explorer.getDirectoryPath() + "/" + fileName;

    if (stat(fullPath.c_str(), &info) == 0 && S_ISDIR(info.st_mode)) {
      if (fileName != "." && fileName != "..") {
        Media media = getFiles(fileName, Explorer);
        if (!media.mediaPath.empty()) {
          Explorer.Medias.push_back(media);
        }
      }
    }
  }
  closedir(dir);
#endif
}

Media getFiles(const std::string& folderName, Explorer& Explorer) {
  // VALID MEDIA FILES
  const char* const file_ext_mp4 = ".mp4";
  const char* const file_ext_m4v = ".m4v";
  const char* const file_ext_mkv = ".mkv";
  const char* const file_ext_avi = ".avi";

  // VALID IMAGE FILES
  const char* const file_ext_png = ".png";
  const char* const file_ext_jpg = ".jpg";

  std::string fullPath = Explorer.getDirectoryPath() + "\\" + folderName;
  Media media;

#ifdef _WIN32
  WIN32_FIND_DATA findFiles;
  HANDLE fileFind = FindFirstFile((fullPath + "\\*").c_str(), &findFiles);

  if(fileFind != INVALID_HANDLE_VALUE) {
    while(FindNextFile(fileFind, &findFiles) != 0) {
      if(!media.mediaPath.empty() && !media.image.imagePath.empty()) break; // Found valid media & image file
      std::string fileName = findFiles.cFileName;
      if(!(findFiles.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        if (fileName != "." && fileName != "..") {
          // If it is a valid movie file
          if (fileName.substr(fileName.length() - 4) == file_ext_mp4 || fileName.substr(fileName.length() - 4) == file_ext_m4v || fileName.substr(fileName.length() - 4) == file_ext_mkv) {
            media.mediaPath = fullPath + "\\" + fileName;
          }
          // If it is a valid media file
          else if (fileName.substr(fileName.length() - 4) == file_ext_png || fileName.substr(fileName.length() - 4) == file_ext_jpg) {
            media.image.imagePath = fullPath + "\\" + fileName;
          }
        }
      }
    }
  }
  FindClose(fileFind);
#else
  DIR* dir = opendir(fullPath.c_str());
  if (dir == nullptr) {
    return media;
  }

  struct dirent* entry;
  while ((entry = readdir(dir)) != nullptr) {
    if (!media.mediaPath.empty() && !media.image.imagePath.empty()) break;
    std::string fileName = entry->d_name;
    struct stat info;
    std::string fullFilePath = fullPath + "/" + fileName;

    if (stat(fullFilePath.c_str(), &info) == 0 && S_ISREG(info.st_mode)) {
      if (fileName != "." && fileName != "..") {
        // Valid media or image file
        if (fileName.substr(fileName.length() - 4) == file_ext_mp4 ||
            fileName.substr(fileName.length() - 4) == file_ext_m4v ||
            fileName.substr(fileName.length() - 4) == file_ext_mkv) {
          media.mediaPath = fileName;
            } else if (fileName.substr(fileName.length() - 4) == file_ext_png ||
                       fileName.substr(fileName.length() - 4) == file_ext_jpg) {
              media.image.imagePath = fileName;
                       }
      }
    }
  }
  closedir(dir)
#endif

  if(media.mediaPath.empty()) return media; // No valid movie file found

  if(media.image.imagePath.empty()){}; // CREATE DEFAULT IMAGE

  media.mediaName = folderName;
  std::cout << media.mediaPath;
  return media;
}

std::string const Explorer::getMedia(const std::string MediaName) {
  for (const auto& Media : Medias) {
    if (Media.mediaName == MediaName) {
      return Media.mediaPath;
    }
  }
  return std::string(); // An empty string if no match
}

std::string const Explorer::getMedia(const int index) {
  if (index < Medias.size() && index >= 0) {
    return Medias[index].mediaPath;
  }
  return std::string(); // An empty string if no match
}

std::string Explorer::getImage(const std::string MediaName) {
  for (const auto& Media : Medias) {
    if (Media.mediaName == MediaName) {
      return Media.image.imagePath;
    }
  }
  return std::string(); // An empty string if no match
}

std::string Explorer::getImage(const int index) {
  if (index < Medias.size() && index >= 0) {
    return Medias[index].mediaPath;
  }
  return std::string(); // An empty string if no match
}
