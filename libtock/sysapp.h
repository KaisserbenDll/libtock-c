#pragma once

#include "tock.h"

#ifdef __cplusplus
extern "C" {
#endif
//refedine this in vpp.h
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

// send_command_main_mgt 
// 1) fills a data structure to the command to beexecuted and map
// it on the IPC_MK_MAIN_MGT_ID
// 2) Send the signal MK_SIGNAL_IPC_UPDATED to the mailbox MK_MAILBOX_MAIN_MGT_ID
// 3) Wait for the signal MK_IPC_UPDATED on the MK_MAILBOX_MGT_MAIN_ID
// 4) Read the response from a data structure through the IPC MK_IPC_MGT_MAIN_ID

//int send_command_main_mgt(int command);

#ifdef __cplusplus
}
#endif