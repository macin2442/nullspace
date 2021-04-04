#ifndef NULLSPACE_CHECKSUM_H_
#define NULLSPACE_CHECKSUM_H_

#include "Types.h"

namespace null {

u8 crc8(const u8* ptr, size_t len);
u32 crc32(const u8* ptr, size_t size);

}  // namespace null

#endif
