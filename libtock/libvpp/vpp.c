#include "libvpp/vpp.h"
#include "tock.h"
#include "libvpp/nvm.h"

// Generic Functions
MK_ERROR_e _mk_Get_Error(MK_HANDLE_t _hProcess){
    return command(VPP_DRIVER_NUM, 100, _hProcess, 0);
 }

MK_TIME_t _mk_Get_Time(void){
    return (MK_TIME_t) command(DRIVER_NUM_ALARM,2,0,0);
};

// Process Management
MK_HANDLE_t _mk_Get_Process_Handle(MK_PROCESS_ID_u _eProcess_ID){
    return command(VPP_DRIVER_NUM, 1, _eProcess_ID, 0);
}


// Mailbox Management 
MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID){
    return command(VPP_DRIVER_NUM, 5, _eMailboxID, 0);

}
MK_ERROR_e _mk_Send_Signal(MK_HANDLE_t _hMailbox, MK_BITMAP_t _eSignal){
    return command(VPP_DRIVER_NUM,6,_hMailbox,_eSignal);
}
MK_BITMAP_t _mk_Get_Signal(MK_HANDLE_t _hMailbox){
    return command(VPP_DRIVER_NUM,7,_hMailbox,0);
}

bool signal_found_or_timeout = false;
static void cb( __attribute__ ((unused)) int unused0,
         __attribute__ ((unused)) int unused1,
         __attribute__ ((unused)) int unused2, 
         __attribute__ ((unused)) void* ud) {
      signal_found_or_timeout = true;
 }

void _mk_Wait_Signal(MK_HANDLE_t _hMailbox,__attribute__ ((unused)) uint32_t _utime){
   __attribute__ ((unused)) int res = subscribe(VPP_DRIVER_NUM,_hMailbox,cb,NULL);
    yield_for(&signal_found_or_timeout); 
} 

// IPC Management
MK_HANDLE_t _mk_Get_IPC_Handle(MK_IPC_ID_u _eIPC_ID){
    return command(VPP_DRIVER_NUM, 21, _eIPC_ID, 0);
}

void* _mk_Get_Access_IPC( MK_HANDLE_t _hIPC){
    int ret =  command(VPP_DRIVER_NUM,15,_hIPC,0);
     return (void*) ret;
}

uint8_t* get_adress_nvm_memory(void){
    int ret = command(VPP_DRIVER_NUM,30,0,0);
    return (uint8_t*) ret;
}

uint8_t Extract_Command_Code(void* ptr){
    uint8_t command_code_t = *((uint8_t*) ptr);
    return command_code_t; 

}
void* allow_ipc(void){
    void* buffer;
    buffer = malloc(MK_IPC_MGT_LENGTH);
   __attribute__ ((unused)) int res = allow(VPP_DRIVER_NUM, 0, (void*) buffer, MK_IPC_MGT_LENGTH);
    return buffer;
}


int test_tbf_head(void){
    int res = command(VPP_DRIVER_NUM,30,0,0);
    return res;
}