#ifndef CRCMODBUS_H
#define CRCMODBUS_H

//class CRCMODBUS
//{
//public:
//    CRCMODBUS();
//};
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

uint16_t ModRTU_CRC(uint8_t* buf, int len);

#ifdef __cplusplus
}
#endif

#endif // CRCMODBUS_H
