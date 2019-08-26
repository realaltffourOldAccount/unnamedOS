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
	for (int i = 3; i < 36; i++)
		if (iso._boot0buff[i] != byte8()) {
			std::cout << "Invalid biosParamBlock, expected 0x00.\n";
			exit(1);
		}
	
	// Check extendedBiosParamBlock
	for (int i = 36; i < 62; i++)
		if (iso._boot0buff[i] != byte8()) {
			std::cout << "Invalid extendedBiosparamblock, expected 0x00.\n";
			exit(1);
		}
	
	// Load bootCode
	for (int i = 62, c = 0; i < 510; i++)
		bootSector.bootCode[c] = iso._boot0buff[i];

	// Load bootSign
	for (int i = 510, c = 0; i < 512; i++)
		bootSector.bootSign[c] = iso._boot0buff[i];

	// Generate fat16 bootsector information.
	fat16_genBoot(iso);
}

auto fat16_genBoot(ISOinfo& iso)->void {
	// Set-up BIOS Parameter Block

	// Set oem id to ISOGEN
	std::string oem = "FreeDOS ";
	for (int i = 0; i < 8; i++)
		bootSector.biosParamBlock->oem_id[i] = oem[i];

	// Set Bytes Per Sector to 512
	bootSector.biosParamBlock->bytesPerSector[0] = byte8(2);
	bootSector.biosParamBlock->bytesPerSector[1] = byte8();

	// Set reserved sectors to (boot1siz/512)+2.
	int reserved = (iso._boot1siz/512)+2;
	if (is8bitDecimal(reserved)) {
		bootSector.biosParamBlock->reservedSectors[0] = byte8(reserved);
	}
	else {
		// Check if reserved can fit to two bytes.
		if (!isxbitDecimal(reserved, 16 /*8x2*/)) {
			std::cout << "Size of boot1 is larger than: " << (2^16) << "\n";
			exit(1);
		}
		std::bitset<16> tempres(reserved);
		for (int i = 0; i < 8; i++)
			bootSector.biosParamBlock->reservedSectors[0][i] = tempres[i];
		for (int i = 0; i < 8; i++)
			bootSector.biosParamBlock->reservedSectors[1][i] = tempres[i+8];
	}

	// Set number of FATs two one.
	bootSector.biosParamBlock->numFAT[0] = byte8(1);

	// Set number of directory entries to 512 (comp with MSDOS).
	bootSector.biosParamBlock->numDirEntry[0] = byte8(2);
	bootSector.biosParamBlock->numDirEntry[1] = byte8(0);

	// Set total sectors in logical volume.

	// Check if ISO size can fit in 2 bytes.
	if (isxbitDecimal((iso._buffSize/512), 16 /*8x2*/)) {
		std::bitset<16> tempsiz(iso._buffSize);
		for (int i = 0; i < 8; i++)
			bootSector.biosParamBlock->totalSectors[0][i] = tempsiz[i];
		for (int i = 0; i < 8; i++)
			bootSector.biosParamBlock->totalSectors[1][i] = tempsiz[i+8];
	}

	// Set mediaDescriptor type.
	bootSector.biosParamBlock->mediaDescriptor[0] = byte8("255");

	// Set number of sectors per FAT to 9 // TODO: check number.
	bootSector.biosParamBlock->sectorPerFAT[0] = byte8(9);
	bootSector.biosParamBlock->sectorPerFAT[1] = byte8(1);

	// Set number of heads to one.
	bootSector.biosParamBlock->numHeads[0] = byte8(1);
	bootSector.biosParamBlock->numHeads[1] = byte8();

	// Set number of hidden sectors.
	bootSector.biosParamBlock->numHiddenSec[0] = byte8();
	bootSector.biosParamBlock->numHiddenSec[1] = byte8();

	// Set Large sector count.

	// Check if count is large enough.
	if (!isxbitDecimal((iso._buffSize/512), 16)) {
		std::bitset<8*4> tempsiz(iso._buffSize);

		for (int i = 0; i < 8; i++)
			bootSector.biosParamBlock->largeSecCnt[0][i] = tempsiz[i];
		for (int i = 0; i < 8; i++)
			bootSector.biosParamBlock->largeSecCnt[1][i] = tempsiz[i+8];
		for (int i = 0; i < 8; i++)
			bootSector.biosParamBlock->largeSecCnt[2][i] = tempsiz[i+(8*2)];
		for (int i = 0; i < 8; i++)
			bootSector.biosParamBlock->largeSecCnt[3][i] = tempsiz[i+(8*3)];
	}

	///////////////////////////////////////////////////////

	// Set-up Extended BIOS Block.

	// Set up drive Number
	bootSector.extendedBiosParamBlock->driveNum[0] = hex2byte8("0x80");

	// Set up windows NT flags.
	bootSector.extendedBiosParamBlock->winNTFlags[0] = byte8();

	// Set up signature flag.
	bootSector.extendedBiosParamBlock->signature[0] = hex2byte8("0x28");

	// Leave volume ID as is.

	// Set up volume label to ISO
	std::string label = "ISO        ";
	for (int i = 0; i < label.size(); i++) {
		bootSector.extendedBiosParamBlock->volLabel[i] = byte8(label[i]);
	}

	// Set up system fle system name.
	std::string sysID = "FAT16   ";
	for (int i = 0; i < sysID.size(); i++) {
		bootSector.extendedBiosParamBlock->sysIDstr[i] = byte8(sysID[i]);
	}
}

auto fat16_write_boot0(ISOinfo& iso)->void {}

auto fat16_format_iso(ISOinfo& iso)->void {}

auto fat16_write_boot1(ISOinfo& iso)->void {}

auto fat16_write_isodir(ISOinfo& iso)->void {} 
