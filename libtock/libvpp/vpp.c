#include "libvpp/vpp.h"
#include "tock.h"
#include "libvpp/nvm.h"

// Generic Functions
MK_BITMAP_t _mk_Get_Exception(__attribute__ ((unused)) MK_HANDLE_t _hProcess){
    return (MK_BITMAP_t) command(VPP_DRIVER_NUM, 1, 0, 0);
}
MK_ERROR_e _mk_Get_Error(MK_HANDLE_t _hProcess){
    return command(VPP_DRIVER_NUM, 2, _hProcess, 0);
}

MK_TIME_t _mk_Get_Time(void){
    return (MK_TIME_t) command(DRIVER_NUM_ALARM,2,0,0);
};

// Process Management
MK_HANDLE_t _mk_Get_Process_Handle(MK_PROCESS_ID_u _eProcess_ID){
    return command(VPP_DRIVER_NUM, 4, _eProcess_ID, 0);
}
MK_PROCESS_PRIORITY_e _mk_Get_Process_Priority(MK_HANDLE_t _hProcess){
    return command(VPP_DRIVER_NUM, 5, _hProcess, 0);
}

MK_ERROR_e _mk_Set_Process_Priority(MK_HANDLE_t _hProcess, MK_PROCESS_PRIORITY_e _xPriority){
    return command(VPP_DRIVER_NUM, 6, _hProcess,_xPriority);
}
MK_ERROR_e _mk_Suspend_Process(MK_HANDLE_t _hProcess){
    return command(VPP_DRIVER_NUM, 7, _hProcess,0);
}
MK_ERROR_e _mk_Resume_Process(MK_HANDLE_t _hProcess){
    return command(VPP_DRIVER_NUM, 8, _hProcess,0);
}
void_mk_Commit(void){
    // This is n.a for Tock processes so it is an empty syscall
   __attribute__ ((unused)) int ret = command(VPP_DRIVER_NUM,9,0,0);
}
void_mk_RollBack(void){
    // This is n.a for Tock processes so it is an empty syscall
   __attribute__ ((unused)) int ret = command(VPP_DRIVER_NUM,10,0,0);
}
void_mk_Yield(void){
    __attribute__ ((unused)) int ret = command(VPP_DRIVER_NUM,11,0,0);
}

// Mailbox Management 
MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID){
    return command(VPP_DRIVER_NUM, 12, _eMailboxID, 0);

}
MK_ERROR_e _mk_Send_Signal(MK_HANDLE_t _hMailbox, MK_BITMAP_t _eSignal){
    return command(VPP_DRIVER_NUM,13,_hMailbox,_eSignal);
}
MK_BITMAP_t _mk_Get_Signal(MK_HANDLE_t _hMailbox){
    return command(VPP_DRIVER_NUM,14,_hMailbox,0);
}

bool signal_found = false;
static void cb( __attribute__ ((unused)) int signals,
         __attribute__ ((unused)) int unused1,
         __attribute__ ((unused)) int unused2, 
         __attribute__ ((unused)) void* ud) {
      signal_found = true;
 }

void _mk_Wait_Signal(MK_HANDLE_t _hMailbox,__attribute__ ((unused)) uint32_t _utime){
   __attribute__ ((unused)) int res = subscribe(VPP_DRIVER_NUM,_hMailbox,cb,NULL);
    yield_for(&signal_found); 
    signal_found = false;
} 

// IPC Management
MK_HANDLE_t _mk_Get_IPC_Handle(MK_IPC_ID_u _eIPC_ID){
    return command(VPP_DRIVER_NUM, 15, _eIPC_ID, 0);
}

void* _mk_Get_Access_IPC( MK_HANDLE_t _hIPC){
    int ret =  command(VPP_DRIVER_NUM,16,_hIPC,0);
     return (void*) ret;
}

uint8_t Extract_Command_Code(void* ptr){
    uint8_t command_code_t = *((uint8_t*) ptr);
    return command_code_t; 

}