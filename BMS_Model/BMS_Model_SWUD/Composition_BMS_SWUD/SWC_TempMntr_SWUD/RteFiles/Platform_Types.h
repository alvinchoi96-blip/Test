#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#define TRUE 1U
#define FALSE 0U
#define CPU_TYPE_8 8U
#define CPU_TYPE_16 16U
#define CPU_TYPE_32 32U
#define MSB_FIRST 0U
#define LSB_FIRST 1U
#define HIGH_BYTE_FIRST 0U
#define LOW_BYTE_FIRST 1U
#define CPU_TYPE CPU_TYPE_32
#define CPU_BIT_ORDER MSB_FIRST
#define CPU_BYTE_ORDER LOW_BYTE_FIRST

typedef unsigned char uint8;
typedef char sint8;
typedef short sint16;
typedef int sint32;
typedef long long sint64;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long	uint64;
typedef int sint8_least;
typedef int sint16_least;
typedef int sint32_least;
typedef unsigned int uint8_least;
typedef unsigned int uint16_least;
typedef unsigned int uint32_least;
typedef float float32;
typedef double float64;
typedef unsigned char boolean;
typedef char AUTOSAR_sint8;
typedef int AUTOSAR_sint8_least;
typedef short AUTOSAR_sint16;
typedef int AUTOSAR_sint16_least;
typedef int AUTOSAR_sint32;
typedef int AUTOSAR_sint32_least;
typedef long long AUTOSAR_sint64;
typedef unsigned char AUTOSAR_uint8;
typedef unsigned int AUTOSAR_uint8_least;
typedef unsigned short AUTOSAR_uint16;
typedef unsigned int AUTOSAR_uint16_least;
typedef unsigned int AUTOSAR_uint32;
typedef unsigned int AUTOSAR_uint32_least;
typedef unsigned long long	AUTOSAR_uint64;
typedef float AUTOSAR_float32;
typedef double AUTOSAR_float64;
typedef unsigned char AUTOSAR_boolean;

#endif