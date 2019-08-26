#ifndef FAT16_GENERATOR_H
#define FAT16_GENERATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../defs.h"
#include "../helper.h"

#include "../byte8/byte8.h"

// FAT16 Definitions.
struct FAT16_BootSector;
struct FAT16_BPB;
struct FAT16_EBPB;

struct FAT16_BootSector {
	byte8 jmpInst[3] = {0}; // inst: JMP SHORT 3C NOP, to skip BPB, EPBP. off: 0, siz: 3
	FAT16_BPB* biosParamBlock = nullptr; // off: 3, siz: 33
	FAT16_EBPB* extendedBiosParamBlock = nullptr; // off: 36, siz: 26
	byte8 bootCode[448] = {0}; // boot code. off: 62, siz: 448
	byte8 bootSign[2] = {0}; // boot signature. off: 510, siz: 2
};
struct FAT16_BPB /* BOIS Parameter Block */ {
	byte8 oem_id[8] = {0}; // oem identifier. off: 3, siz: 8
	byte8 bytesPerSector[2] = {0}; // bytes per sector. off: 11, siz: 2
	byte8 sectorsPerCluster[1] = {0}; // sectors per cluster. off: 13, siz: 1
	byte8 reservedSectors[2] = {0}; // reserved sectors (+boot). off: 14, siz: 2
	byte8 numFAT[1] = {0}; // number of FATs. off: 16, siz: 1
	byte8 numDirEntry[2] = {0}; // number of dir. entries. off: 17, siz: 2
	byte8 totalSectors[2] = {0}; // total sectors in logical vol. off: 19, siz: 2
	byte8 mediaDescriptor[1] = {0}; // media descriptor type. off: 21, siz: 1
	byte8 sectorPerFAT[2] = {0}; // number of sectors per FAT. off: 22, siz: 2
	byte8 sectorPerTrack[2] = {0}; // number of sectors per Track. off: 24, siz: 2
	byte8 numHeads[2] = {0}; // number of heads or sides. off: 26, siz: 2
	byte8 numHiddenSec[4] = {0}; // number of hidden sectors. off: 28, siz: 4
	byte8 largeSecCnt[4] = {0}; // Large sector count. off: 32, siz: 4	
};
struct FAT16_EBPB /* Extended BOIS Parameter Block */ {
	byte8 driveNum[1] = {0}; // drive number passed by the BIOS. off: 36, siz: 1
	byte8 winNTFlags[1] = {0}; // windows NT, reserved. off: 37, siz: 1
	byte8 signature[1] = {0}; // signature. off: 38, siz: 1
	byte8 volID[4] = {0}; // VolumeID serial number. off: 36, siz: 4
	byte8 volLabel[11] = {0}; // Volume label string. off: 40, siz: 11
	byte8 sysIDstr[8] = {0}; // System Identifier string. off: 51, siz: 8
	; // boot code. off: 62, siz: 448
};

static FAT16_BootSector bootSector;

auto fat16_init(ISOinfo& iso)->void;
auto fat16_genBoot(ISOinfo& iso)->void;
auto fat16_format_iso(ISOinfo& iso)->void;

auto fat16_write_boot0(ISOinfo& iso)->void;

auto fat16_write_boot1(ISOinfo& iso)->void;
auto fat16_write_isodir(ISOinfo& iso)->void;

#endif
