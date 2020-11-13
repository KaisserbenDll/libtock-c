#pragma once
#include "tock.h"
#ifdef __cplusplus
extern "C" {
#endif
#define VPP_DRIVER_NUM 0x90100
#define DRIVER_NUM_ALARM 0x0

// Index of an element in a typed array 
typedef uint16_t MK_Index_t;

typedef uint32_t MK_HANDLE_t;
typedef uint64_t MK_TIME_t;
// Identifiers need to be changed
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
    MK_ERROR_HANDLE_NOT_ACCESSED = 9, 
    MK_ERROR_GET_ERROR_HANDLE_NOT_A_PROCESS = 10,
    MK_ERROR_VENDOR_BASE = 32,
    MK_ERROR_MAX = 255,
} MK_ERROR_e ;
 
 // Gerneric Functions 
    // MK_BITMAP_t _mk_Get_Exception(MK_HANDLE_t _hProcess);
    MK_ERROR_e _mk_Get_Error(MK_HANDLE_t _hProcess);
    MK_TIME_t _mk_Get_Time(void);

// Process Management 
    MK_HANDLE_t _mk_Get_Process_Handle(MK_PROCESS_ID_u _eProcess_ID);
    //MK_ERROR_e _mk_Set_Process_Priority(MK_HANDLE_t _hProcess, MK_PROCESS_PRIORITY_e _xPriority);
    // MK_ERROR_e _mk_Suspend_Process(MK_HANDLE_t _hProcess);
    // MK_ERROR_e _mk_Resume_Process(MK_HANDLE_t _hProcess);
    //MK_ERROR_e _mk_Request_No_Preemption(uint32_t _uTime);
    // void_mk_Commit(void);
    // void_mk_RollBack(void);
    // void_mk_Yield(void);



// Mailbox Management 
//    MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID)
// Get a Mailbox Handle from a Mailbox Identifier 
MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID);
// Send a Signal to a specific mailbox
MK_ERROR_e _mk_Send_Signal(MK_HANDLE_t _hMailbox, MK_BITMAP_t _eSignal);
// Retrieve last Signal from Mailbox. Signals are cleared once read.
MK_BITMAP_t _mk_Get_Signal(MK_HANDLE_t _hMailbox);


// IPC Management 


//void* _mk_Get_Access_IPC (MK_HANDLE_t _hIPC);
//char shared_bufff[64] __attribute__((aligned(64)));
//int Share_Slice(MK_HANDLE_t _hIPC);

// Firmware Management
// misc
const char *buf[128] __attribute__((aligned(64)));

const char* register_share(void);

int some_subscribe_test(MK_HANDLE_t _hIPC, subscribe_cb callback,  void* ud);

#ifdef __cplusplus
}
#endif