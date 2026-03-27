cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(ABI_PhysFS_Loader)

# Add PhysFS via FetchContent
include(FetchContent)

set(PHYSFS_BUILD_SHARED OFF CACHE BOOL "" FORCE)
set(PHYSFS_BUILD_TEST   OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  physfs
  GIT_REPOSITORY https://github.com/icculus/physfs.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(physfs)

add_library(ABI_PhysFS_Loader INTERFACE)

target_compile_features(ABI_PhysFS_Loader INTERFACE cxx_std_17)

# Expose headers so consumers can #include "ABI_PhysFS_Loader.h"
target_include_directories(ABI_PhysFS_Loader INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
)

# INTERFACE so consumers transitively get physfs include dirs (needed for physfs.h in our header)
target_link_libraries(ABI_PhysFS_Loader INTERFACE PhysFS::PhysFS-static)
