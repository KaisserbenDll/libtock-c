#pragma once

#include "tock.h"

#ifdef __cplusplus
extern "C" {
#endif

//refedine this in vpp.h
typedef uint32_t MK_HANDLE_t;
typedef uint16_t MK_PROCESS_ID_u;
typedef uint16_t MK_MAILBOX_ID_u;
typedef uint32_t MK_BITMAP_t;
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
#define VPP_DRIVER_NUM 0x90100

// Get a Mailbox Handle from a Mailbox Identifier 
MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID);
// Send a Signal to a specific mailbox
MK_ERROR_e _mk_Send_Signal(MK_HANDLE_t _hMailbox, MK_BITMAP_t _eSignal);
// Retrieve last Signal from Mailbox. Signals are cleared once read.
MK_BITMAP_t _mk_Get_Signal(MK_HANDLE_t _hMailbox);

#ifdef __cplusplus
}
#endif