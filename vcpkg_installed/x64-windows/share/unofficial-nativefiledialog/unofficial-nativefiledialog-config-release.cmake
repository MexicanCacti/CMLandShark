#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::nativefiledialog::nfd" for configuration "Release"
set_property(TARGET unofficial::nativefiledialog::nfd APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(unofficial::nativefiledialog::nfd PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/nfd.lib"
  )

list(APPEND _cmake_import_check_targets unofficial::nativefiledialog::nfd )
list(APPEND _cmake_import_check_files_for_unofficial::nativefiledialog::nfd "${_IMPORT_PREFIX}/lib/nfd.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
