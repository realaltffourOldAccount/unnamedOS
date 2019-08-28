#include "generator.h"

auto generate_iso(ISOinfo& iso)->void {
    // Allocate ISO buffer.
    // Convert from Megabyte to bytes
	iso._buffSize = iso._buffSize * (1024*1024);
	
    iso._buff = byte8_malloc(iso._buffSize);

    // Configure the generator system.
    switch (iso._fs) {
    case FileSystems::FS_FAT16:
        fat16_init(iso);
        break;
    case FileSystems::FS_FAT32:
        //fat32_init(iso);
        break;
    };
    
    // Write boot sector.
    write_boot0(iso);

    // Write second stage boot sector.
    write_boot1(iso);

    // Write the ISO to the output directory.
    writeISO(iso);
	
    // Clean the resources.
    cleanISO(iso);
}

auto write_boot0(ISOinfo& iso)->void {
    switch (iso._fs) {
    case FileSystems::FS_FAT16: 
        fat16_write_boot0(iso);
        break;
    case FileSystems::FS_FAT32:
        //fat32_write_boot0(iso);
        break;
    };
}

auto write_boot1(ISOinfo& iso)->void {
    switch (iso._fs) {
    case FileSystems::FS_FAT16:
        fat16_write_boot1(iso);
        break;
    case FileSystems::FS_FAT32:
        //fat32_write_boot1(iso);
        break;
    };
}

auto write_isodir(ISOinfo& iso)->void {
    switch (iso._fs) {
    case FileSystems::FS_FAT16:
        fat16_write_isodir(iso);
        break;
    case FileSystems::FS_FAT32:
        //fat32_write_isodir(iso);
        break;
    };
}

auto writeISO(const ISOinfo& iso)->void {
    // TODO: Implement this.
	std::ofstream stream("test.iso", std::ios::binary);

	for (int i = 0; i < iso._buffSize; i++) {
		stream << iso._buff[i];
	}
	
	//	out.flush();
	stream.close();
}

auto cleanISO(ISOinfo& iso)->void {
    // Free allocated ISO buffer memory.
    free(iso._buff);
}
