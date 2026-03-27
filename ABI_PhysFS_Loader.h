#pragma once
#include <physfs.h>

// Load a package (zip file) into the PhysFS search path. Returns true on success.
inline bool ABI_PhysFS_Load_Package(const char* zipPath, const char* mountPoint = "/", bool appendToPath = true) {
    if (!PHYSFS_isInit()) {
        if (!PHYSFS_init(nullptr)) {
            return false;
        }
    }
    return PHYSFS_mount(zipPath, mountPoint, appendToPath) != 0;
}

// Check if a package (zip file) is already loaded in the PhysFS search path. Returns true if found.
inline bool ABI_PhysFS_Check_Package_Loaded(const char* zipPath) {

    if (!PHYSFS_isInit()) return false;

    char **mounts = PHYSFS_getSearchPath();
    if (!mounts) return false;
    bool found = false;
    for (char **p = mounts; *p != nullptr; ++p) {
        const char *a = zipPath, *b = *p;
        while (*a && (*a == *b)) { ++a; ++b; }
        if (*a == *b) {
            found = true;
            break;
        }
    }
    PHYSFS_freeList(mounts);
    return found;
}

// Check if a file exists in the PhysFS search path. Returns true if found.
inline bool ABI_PhysFS_Check_File_Exists(const char* filePath) {
    if (!PHYSFS_isInit()) return false;
    return PHYSFS_exists(filePath) != 0;
}

// Get the contents of a file from the PhysFS search path. Returns a pointer to the file data and optionally sets the file size.
inline void* ABI_PhysFS_Get_File_Contents(const char* filePath, PHYSFS_sint64* outSize = nullptr) {

    if (!PHYSFS_isInit()) return nullptr;

    if (outSize) *outSize = 0;
    PHYSFS_File* file = PHYSFS_openRead(filePath);
    if (!file) return nullptr;
    PHYSFS_sint64 size = PHYSFS_fileLength(file);
    if (size <= 0) {
        PHYSFS_close(file);
        return nullptr;
    }
    void* buffer = PHYSFS_getAllocator()->Malloc(static_cast<PHYSFS_sint64>(size));
    if (!buffer) {
        PHYSFS_close(file);
        return nullptr;
    }
    PHYSFS_sint64 readBytes = PHYSFS_readBytes(file, buffer, size);
    PHYSFS_close(file);
    if (readBytes != size) {
        PHYSFS_getAllocator()->Free(buffer);
        return nullptr;
    }
    if (outSize) *outSize = size;
    return buffer;
}

// Free the memory allocated for file contents retrieved by ABI_PhysFS_Get_File_Contents.
inline void ABI_PhysFS_Free_File_Contents(void* buffer) {
    if (PHYSFS_isInit()) {
        if (buffer) {
            PHYSFS_getAllocator()->Free(buffer);
        }
    }
}

// Unload a package (zip file) from the PhysFS search path.
inline void ABI_PhysFS_Unload_Package(const char* zipPath) {
    if (PHYSFS_isInit()) {
        PHYSFS_unmount(zipPath);
    }
}

// Deinitialize PhysFS and free resources.
inline void ABI_PhysFS_Destroy() {
    if (PHYSFS_isInit()) {
        PHYSFS_deinit();
    }
}