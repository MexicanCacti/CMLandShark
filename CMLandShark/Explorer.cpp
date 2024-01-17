#include "Explorer.h"
Media const Explorer::getMedia(const std::string MediaName) {
  for (const auto& Media : Medias) {
    if (Media.mediaName == MediaName) {
      return Media;
    }
  }
  return Dummy;
}

Media const Explorer::getMedia(const int index) {
  if (index > Medias.size() || index < 0) {
    return Dummy;  // empty media object. make sure to handle if empty!
  }
  return Medias[index];
}

Image Explorer::getImage(const std::string MediaName) {
  for (const auto& Media : Medias) {
    if (Media.mediaName == MediaName) {
      return Media.image;
    }
  }
  return Dummy.image;
}

Image Explorer::getImage(const int index) {
  if (index > Medias.size() || index < 0) {
    return Dummy.image;  // empty media object. make sure to handle if empty!
  }
  return Medias[index].image;
}
