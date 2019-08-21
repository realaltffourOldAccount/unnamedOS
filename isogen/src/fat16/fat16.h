#ifndef FAT16_GENERATOR_H
#define FAT16_GENERATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../defs.h"
#include "../helper.h"

// FAT16 Definitions.
struct FAT16_BootSector {};
struct FAT16_BPB /* BOIS Parameter Block */ {};
struct FAT16_EBPB /* Extended BOIS Parameter Block */ {};

auto fat16_init(const ISOinfo& iso)->void;
auto fat16_write_boot0(ISOinfo& iso)->void;
auto fat16_format_iso(ISOinfo& iso)->void;
auto fat16_write_boot1(ISOinfo& iso)->void;
auto fat16_write_isodir(ISOinfo& iso)->void;

#endif
