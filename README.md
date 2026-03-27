# ABI_PhysFS_Loader

A Simple wrapper for PhysFS to load and access the contents of .zip's and other package files easily.

# Usage

```cpp
#include "ABI_PhysFS_Loader.h"

// Load a package (zip file) into the PhysFS search path. Returns true on success.
bool ABI_PhysFS_Load_Package(const char* zipPath, const char* mountPoint = "/", bool appendToPath = true);

// Check if a package (zip file) is already loaded in the PhysFS search path. Returns true if found.
bool ABI_PhysFS_Check_Package_Loaded(const char* zipPath);

// Check if a file exists in the PhysFS search path. Returns true if found.
bool ABI_PhysFS_Check_File_Exists(const char* filePath);

// Get the contents of a file from the PhysFS search path. Returns a pointer to the file data and optionally sets the file size.
void* ABI_PhysFS_Get_File_Contents(const char* filePath, PHYSFS_sint64* outSize = nullptr);

// Free the memory allocated for file contents retrieved by ABI_PhysFS_Get_File_Contents.
void ABI_PhysFS_Free_File_Contents(void* buffer);

// Unload a package (zip file) from the PhysFS search path.
void ABI_PhysFS_Unload_Package(const char* zipPath);

// Deinitialize PhysFS and free resources.
void ABI_PhysFS_Destroy();
```

# Build instructions
## AUTOMATED INSTALL (CMAKE)

```cmake
# Get PhysFS
include(FetchContent)

FetchContent_Declare(
  physfs
  GIT_REPOSITORY https://github.com/icculus/physfs.git
  GIT_TAG main
)
FetchContent_MakeAvailable(physfs)

# If you have `ABI_PhysFS_Loader` cloned locally, set `""` to its location to avoid fetching it from GitHub.
set(ABI_PhysFS_Loader_LOCAL_PATH "" CACHE PATH "CACHE_ABI_PhysFS_Loader" FORCE)

if(ABI_PhysFS_Loader_LOCAL_PATH)
  FetchContent_Declare(
    ABI_PhysFS_Loader
    SOURCE_DIR ${ABI_PhysFS_Loader_LOCAL_PATH}
  )
else()
  FetchContent_Declare(
    ABI_PhysFS_Loader
    GIT_REPOSITORY https://github.com/ActingBadly/ABI_PhysFS_Loader.git
    GIT_TAG        main
  )
endif()
FetchContent_MakeAvailable(ABI_PhysFS_Loader)

target_include_directories(ABI_PhysFS_Loader PUBLIC ${ABI_PhysFS_Loader_SOURCE_DIR})

target_link_libraries(APP_NAME PRIVATE
    ABI_PhysFS_Loader
)
```
