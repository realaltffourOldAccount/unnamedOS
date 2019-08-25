#ifndef DEFS_H
#define DEFS_H

#include <string>
#include <map>
#include <vector>
#include "byte8/byte8.h"


// Type Definitions
#define normArgs std::vector<std::string>
#define pairedArgs std::vector<std::pair<std::string, std::vector<std::string>>>

// Files Systems definitions.
enum FileSystems {
                  FS_FAT16 = 0,
                  FS_FAT32 = 1,
};

// Command-Line Arguments
enum CMDArgs {
              FS = 0, // The filesystem type.
              BT0_LOC, // The location of boot0 file.
              BT1_LOC, // The location of boot1 file.
              ISODIR_LOC, // The location of the ISO contents.
              OUTPUT_LOC, // The output location of the ISO.
              ISO_SIZE, // The ISO size in MEGABYTES.
};

// Mapped FileSystem names.
static std::map<std::string, int> mappedFileSysNames = {
                      { "FAT16", FileSystems::FS_FAT16 },
                      { "fat16", FileSystems::FS_FAT16 },
                      { "f16", FileSystems::FS_FAT16 },
                      { "FAT32", FileSystems::FS_FAT16 },
                      { "fat32", FileSystems::FS_FAT32 },
                      { "f32", FileSystems::FS_FAT32 },
};
// Mapped Arguments
static std::map<std::string, int> mappedArgs = {
                      { "--filesystems", CMDArgs::FS },
                      { "--filesys", CMDArgs::FS },
                      { "--fs", CMDArgs::FS },
                      { "-f", CMDArgs::FS },
                      { "--boot0", CMDArgs::BT0_LOC },
                      { "--bt0", CMDArgs::BT0_LOC },
                      { "-a", CMDArgs::BT0_LOC },
                      { "--boot1", CMDArgs::BT1_LOC },
                      { "--bt1", CMDArgs::BT1_LOC },
                      { "-b", CMDArgs::BT1_LOC },
                      { "--isodir", CMDArgs::ISODIR_LOC },
                      { "--dir", CMDArgs::ISODIR_LOC },
                      { "-d", CMDArgs::ISODIR_LOC },
                      { "--outputdir", CMDArgs::OUTPUT_LOC },
                      { "--output", CMDArgs::OUTPUT_LOC },
                      { "-o", CMDArgs::OUTPUT_LOC },
                      { "--size", CMDArgs::ISO_SIZE },
                      { "-s", CMDArgs::ISO_SIZE },
};

// ISO information.
struct ISOinfo {
    FileSystems _fs = static_cast<FileSystems>(-1);
    std::string _boot0_loc = "";
    std::string _boot1_loc = "";
    std::string _dir_loc = "";
    std::string _output_loc = "";
    byte8* _buff = nullptr;
	byte8* _boot0buff = nullptr;
	byte8* _boot1buff = nullptr;
    size_t _buffSize = 0;
};

#endif
