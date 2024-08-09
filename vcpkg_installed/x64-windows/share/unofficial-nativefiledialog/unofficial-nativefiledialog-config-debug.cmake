#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::nativefiledialog::nfd" for configuration "Debug"
set_property(TARGET unofficial::nativefiledialog::nfd APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(unofficial::nativefiledialog::nfd PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/nfd_d.lib"
  )

list(APPEND _cmake_import_check_targets unofficial::nativefiledialog::nfd )
list(APPEND _cmake_import_check_files_for_unofficial::nativefiledialog::nfd "${_IMPORT_PREFIX}/debug/lib/nfd_d.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
