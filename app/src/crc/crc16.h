#ifndef _CRC_CRC16_H
#define _CRC_CRC16_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus  */

uint16_t crc16(const void *buf, size_t len);

#ifdef __cplusplus
}
#endif /* __cplusplus  */
#endif
