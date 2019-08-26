#include "fat16.h"

auto fat16_init(ISOinfo& iso)->void {
	// Allocate boot0 buffer.
	// Boot sector is always 512 bytes.
	iso._boot0buff = byte8_malloc(512);
	
	// Open boot0 and boot1 files.
	std::fstream boot0_stream(iso._boot0_loc, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
	std::fstream boot1_stream(iso._boot1_loc, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);

	// Check if file is open.
	if (!boot0_stream.is_open()) {
		std::cout << "Could not open boot0 file!\n";
		exit(1);
	}

	if (!boot1_stream.is_open()) {
		std::cout << "Could not open boot1 file!\n";
		exit(1);
	}

	// Allocate boot1.
	boot1_stream.seekg(0, std::ios::end);
	iso._boot1buff = byte8_malloc(boot1_stream.tellg());
	iso._boot1siz = boot1_stream.tellg();
	boot1_stream.seekg(0, std::ios::beg);
	
	// Load boot0 and boot1 into their buffers.
	char* boot0_tmp = new char[iso._boot0siz];
	char* boot1_tmp = new char[iso._boot1siz];

    boot0_stream.read(boot0_tmp, iso._boot0siz);
	boot1_stream.read(boot1_tmp, iso._boot1siz);

	byte8_arrset(iso._boot0buff, iso._boot0siz, boot0_tmp);
	byte8_arrset(iso._boot1buff, iso._boot1siz, boot1_tmp);

	// Allocate bootSector members.
	bootSector.biosParamBlock = new FAT16_BPB();
	bootSector.extendedBiosParamBlock = new FAT16_EBPB();
	
	// Load the boot0 and boot1 buffer to proper structures.

	// Load jmp instruction
	for (int i = 0; i < 3; i++)
		bootSector.jmpInst[i] = iso._boot0buff[i];

	// Check biosParamBlock
	for (int i = 3; i < 35; i++)
		if (iso._boot0buff[i] != byte8()) {
			std::cout << "Invalid biosParamBlock, expected 0x00.\n";
			exit(1);
		}
	
	// Load BPBsplit.
	bootSector.BPBsplit[0] = iso._boot0buff[35];

	// Check extendedBiosParamBlock
	for (int i = 36; i < 54; i++)
		if (iso._boot0buff[i] != byte8()) {
			std::cout << "Invalid extendedBiosparamblock, expected 0x00.\n";
			exit(1);
		}
	
	// Load bootCode
	for (int i = 54, c = 0; i < 448; i++)
		bootSector.bootCode[c] = iso._boot0buff[i];

	// Load bootSign
	for (int i = 510, c = 0; i < 512; i++)
		bootSector.bootSign[c] = iso._boot0buff[i];

	// Generate fat16 bootsector information.
	fat16_genBoot(iso);
}

auto fat16_genBoot(ISOinfo& iso)->void {
	
}

auto fat16_write_boot0(ISOinfo& iso)->void {}

auto fat16_format_iso(ISOinfo& iso)->void {}

auto fat16_write_boot1(ISOinfo& iso)->void {}

auto fat16_write_isodir(ISOinfo& iso)->void {} 
