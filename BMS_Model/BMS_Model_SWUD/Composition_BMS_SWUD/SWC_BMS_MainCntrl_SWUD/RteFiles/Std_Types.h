#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Platform_Types.h"
#include "Compiler.h"

#define STD_HIGH 1U
#define STD_LOW 0U
#define STD_ACTIVE 1U
#define STD_IDLE 0U
#define STD_ON 1U
#define STD_OFF 0U
#define E_OK 0U
#define E_NOT_OK 1U

typedef uint8 Std_ReturnType;
typedef unsigned char StatusType;
typedef struct _Std_VersionInfoType_
{
	uint16 vendorID ;
	uint16 moduleID ;
	uint8 sw_major_version ;
	uint8 sw_minor_version ;
	uint8 sw_patch_version ;
}Std_VersionInfoType;

#endif