#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include "defs.h"

#include "fat16/fat16.h"
#include "fat32/fat32.h"

auto generate_iso(ISOinfo& iso)->void;
auto write_boot0(ISOinfo& iso)->void;
auto write_boot1(ISOinfo& iso)->void;
auto write_isodir(ISOinfo& iso)->void;
auto writeISO(const ISOinfo& iso)->void;
auto cleanISO(ISOinfo& iso)->void;
#endif
