#pragma once

#include "tock.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DRIVER_NUM_PM 0x90004
typedef uint32_t MK_HANDLE_t;
typedef uint16_t MK_PROCESS_ID_u;
typedef enum {
    MK_ERROR_NONE = 0, 
    MK_ERROR_UNKNOWN_UUID = 1,
    MK_ERROR_SEVERE = 2,
    MK_ERROR_ILLEGAL_PARAMETER = 3, 
    MK_ERROR_UNKNOWN_ID = 4,
    MK_ERROR_UNKNOWN_HANDLE = 5,
    MK_ERROR_UNKNOWN_PRIORITY = 6, 
    MK_ERROR_ACCESS_DENIED = 7,
    MK_ERROR_INTERNAL = 8,
    MK_ERROR_VENDOR_BASE = 32,
    MK_ERROR_MAX = 255,
} MK_ERROR_e ;
//#define DRIVER_NUM_PM 0x9000A

//MK_HANDLE_t _mk_Get_Process_Handle(MK_PROCESS_ID_u _eProcess_ID);
MK_ERROR_e _mk_Suspend_Process(MK_HANDLE_t _hProcess);
MK_ERROR_e _mk_Resume_Process (MK_HANDLE_t _hProcess);
//void _mk_Yield(MK_HANDLE_t _hProcess);
void _mk_Yield(void);
int _testing (void);

#ifdef __cplusplus
}
#endif