/*******************************************************
 * File name:pando_machine.h
 * Author:    Zhao Wenwu
 * Versions:  0.1
 * Description: APIs related to different machine platform, 
     Such as basic IO operation and some common functions.
 * History:
 *   1.Date:
 *     Author:
 *     Modification:    
 *********************************************************/
 
#ifndef PD_MACHINE_H
#define PD_MACHINE_H

#ifdef ESP8266_PLANTFORM

#include "pando_types.h"
#include "mem.h"
#include "osapi.h"
//#include "../gateway/pando_system_time.h"

// for #pragma pack(ALIGNED_LENGTH), for example, esp8266 should be 1
#define ALIGNED_LENGTH   1

// some platform need this prefix between function name and return type
#define FUNCTION_ATTRIBUTE ICACHE_FLASH_ATTR


// different platform has its own define of these functions.

#define pd_malloc os_malloc
#define pd_free os_free
#define pd_memcpy os_memcpy
#define pd_printf os_printf
#define pd_memcmp os_memcmp
#define pd_memset os_memset

#else
#include "platform/include/pando_types.h"

#define ALIGNED_LENGTH 1

// some platform need this prefix between function name and return type
#define FUNCTION_ATTRIBUTE

// different platform has its own define of these functions.
#define pd_malloc malloc
#define pd_free free
#define pd_memcpy memcpy
#define pd_printf printf
#define pd_memcmp memcmp
#define pd_memset memset

#endif

uint64_t pd_get_timestamp(void);

#endif

