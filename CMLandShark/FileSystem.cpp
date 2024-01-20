#include "FileSystem.h"

void getFolders(Explorer& Explorer) {
  std::vector<std::string>folderNames;  // List of all the folders
  Media media;

  // Locate all the folders in the directory
  for (const auto& file : fs::directory_iterator(Explorer.DirectoryPath)) {
    if (fs::is_regular_file(file)) continue; // Grab all folder paths in the directory
    folderNames.push_back(file.path().string().substr(Explorer.DirectoryPath.length() + 1));
  }

  // For every folder that we found
  for (const auto& folder : folderNames) {
    media = getFiles(folder, Explorer);
    if (media.mediaPath.empty()) continue; // If there is no media file don't add to list of objects
    Explorer.Medias.push_back(media);
  }
}

Media getFiles(std::string folderName, Explorer& Explorer) {
  // VALID MEDIA FILES
  const char* const file_ext_mp4 = ".mp4";
  const char* const file_ext_m4v = ".m4v";
  const char* const file_ext_mkv = ".mkv";
  const char* const file_ext_akv = ".avi";

  // VALID IMAGE FILES
  const char* const file_ext_png = ".png";
  const char* const file_ext_jpg = ".jpg";

  std::string PATH = Explorer.getDirectoryPath() + "\\" + folderName + "\\";
  std::string temp;
  Media media;

  for (const auto& file : fs::directory_iterator(PATH)) {
    if (!media.mediaPath.empty() && !media.image.imagePath.empty()) break; // Found a valid media & image file
    if (fs::is_regular_file(file)) {
      temp = file.path().string();
      // If it is a valid movie file
      if (temp.substr(temp.length() - 4) == file_ext_mp4 || temp.substr(temp.length() - 4) == file_ext_m4v || temp.substr(temp.length() - 4) == file_ext_mkv) {
        media.mediaPath = temp;
      }
      // If it is a valid media file
      else if (temp.substr(temp.length() - 4) == file_ext_png || temp.substr(temp.length() - 4) == file_ext_jpg) {
        media.image.imagePath = temp;
      }
    }
  }

  if (media.mediaPath.empty()) return media;  // No valid media file

  if (media.image.imagePath.empty()) {
    // Create a default image
  }

  media.mediaName = folderName;

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
