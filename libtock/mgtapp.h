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

/*
When a response is to be returned from the MGT Process to the Main Process, 
the MGT Process shall: 
1) Wait for the Signal MK_SIGNAL_IPC_UPDATED on the Mailbox MK_MAILBOX_MAIN_MGT_ID
2) Read the command data through the IPC MK_IPC_MAIN_MGT_ID
3) Send the response data through the IPC MK_IPC_MGT_MAIN_ID
4) Send the Signal MK_SIGNAL_IPC_UPDATED to the Mailbox MK_MAILBOX_MGT_MAIN_ID
*/
int recieve_command_mgt_main(void);
#ifdef __cplusplus
}
#endif