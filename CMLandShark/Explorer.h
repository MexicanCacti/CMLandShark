#pragma once

#ifndef EXPLORER_H
#define EXPLORER_H
#include "FileSystem.h"
// eventually probably want to include a function that sorts everything alphabetically ^_^
class Explorer {
  private:
    std::string DirectoryPath;  // path to the directory containing ALL the medias
    std::vector<Media> Medias;  // list of media folders & their contents
    Media Dummy;
  public:    
    inline void setDirectoryPath(std::string dPath) {DirectoryPath = dPath;}  // sets the path to the directory containing ALL the media files
    inline std::string const getDirectoryPath() {return DirectoryPath; }      // returns the directory path
    inline void findMedia() {getFolders(Medias, DirectoryPath); } // intializes list of movie folders & contents
    inline bool isMissing() {return DirectoryPath.empty(); }  // checks if there is a stored directory path... true if there isn't, false if there is
    inline void clearMedia() {Medias.clear(); }  // clears list of media 
    Media const getMedia(const std::string MediaName);  // returns Media object based on mediaName
    Media const getMedia(const int index);  // returns Media object based on index
    // NON CONST so can change size of image
    Image getImage(const std::string MediaName);  // returns Image object based on name
    Image getImage(const int index);  // returns Media object based on index
    inline std::vector<Media> const getMedias() {return Medias; } // returns the list of medias inside of the directory
    inline int const getAmount() {return Medias.size(); }
};


#endif