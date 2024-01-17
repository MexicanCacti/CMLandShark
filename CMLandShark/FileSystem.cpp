#include "FileSystem.h"
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // to create a default .png if there is no valid image file
void getFolders(std::vector<Media>& Medias, std::string Directory) {
  std::vector<std::string>folderNames;  // list of all the folders
  Media media;
  
  //locate all the folders in the directory
  for (const auto& file : fs::directory_iterator(Directory)) {
    if(fs::is_regular_file(file)) continue; // want to grab all the folder paths in the directory
    folderNames.push_back(file.path().string().substr(Directory.length() + 1)); // ONLY want the folders
  }

  // for every folder that we found
  for (const auto& folder : folderNames) {
    media = getFiles(folder, Directory);
    if (media.mediaPath.empty()) {
      continue; // no valid media file so exclude the folder in the final list of folders
    }
    Medias.push_back(media);
  }
}

Media getFiles(std::string Folder, std::string Directory) {
  bool mediaPathFound = false;
  bool imagePathFound = false;
  std::vector<fs::path> filePaths;
  std::string temp;
  std::string mediaPath;
  std::string imagePath;
  std::string Path = Directory + "\\" + Folder + "\\";
  Media media;
  Image tImage;
  //VALID MEDIA FILES
  const char* const file_ext_mp4 = ".mp4";
  const char* const file_ext_m4v = ".m4v";
  const char* const file_ext_mkv = ".mkv";
  const char* const file_ext_akv = ".avi";
  //VALID IMAGE FILES
  const char* const file_ext_png = ".png";
  const char* const file_ext_jpg = ".jpg";
  
  for (const auto& file : fs::directory_iterator(Path)) {
    if(!mediaPath.empty() && !imagePath.empty()) break; // already found the media and image path so dont check anymore
    if (fs::is_regular_file(file)) {
      temp = file.path().string();
      // if its a valid movie file
      if (temp.substr(temp.length() - 4) == file_ext_mp4 || temp.substr(temp.length() - 4) == file_ext_m4v || temp.substr(temp.length() - 4) == file_ext_mkv) {
        mediaPathFound = true;
        temp.erase(temp.find(Path), Path.length()); // gets rid of path directory to single out media file
        mediaPath = temp;
      }
      // else if its a valid image file
      else if (temp.substr(temp.length() - 4) == file_ext_png || temp.substr(temp.length() - 4) == file_ext_jpg) {
        imagePathFound = true;
        temp.erase(temp.find(Path), Path.length()); // get rid of path directory to single out image file
        // MAYBE HAVE TO ERASE THE .[ ] EXTENSION IDK
        imagePath = temp;
      }
    }
  }
  if (!mediaPathFound) {
    return media;
  }
  
  if (!imagePathFound) {
    imagePath = createDefaultImage(Path);
  }
  
  // set up the media object with the necessary paths
  tImage.imagePath = imagePath;
  media.mediaPath = mediaPath;
  media.mediaName = Folder;
  media.image = tImage;
  return media;
}

std::string createDefaultImage(std::string Path) {
  std::string defaultImage = "defaultImage.png";
  std::string sImagePath = Path + defaultImage;
  const char* filename = sImagePath.c_str();
  int width = 256;  // # of pixels wide
  int height = 256; // # of pixels tall
  
  // create image with data
  // pixels is an array allocated to store RGB pixel data. size of array calc based on image dimensions & color format (3 bytes per pixel for RGB)
  unsigned char* pixels = new unsigned char[width * height * 3];
  
  // fill pixels with image data
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int index = 3 * (y * width + x);
      // set rgb
      pixels[index] = 0;  // red
      pixels[index + 1] = 0; // green
      pixels[index + 2] = 0;  // blue
    }
  }
  
  // write image to a file
  stbi_write_png(filename, width, height, 3, pixels, width * 3);
  // release memory
  delete[] pixels;
  
  return sImagePath;
}