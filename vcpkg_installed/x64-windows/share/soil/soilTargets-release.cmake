#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "soil" for configuration "Release"
set_property(TARGET soil APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(soil PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/soil.lib"
  )

list(APPEND _cmake_import_check_targets soil )
list(APPEND _cmake_import_check_files_for_soil "${_IMPORT_PREFIX}/lib/soil.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
