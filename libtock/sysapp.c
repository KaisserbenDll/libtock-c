#include "sysapp.h"
#include "tock.h"

/*
int send_command_main_mgt(int command){

    MK_HANDLE_t mgt_ipc_handle =_mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
    
    int* shared_mem_ptr = _mk_Get_Access_IPC(mgt_ipc_handle);
    size_t len_command = strlen(command);
    // this is mapping the command to be executed on the IPC
    memcpy(shared_mem_ptr,command,len_command);

    MK_HANDLE_t mgt_mb_handle = _mk_Get_Mailbox_Handle(MK_MAILBOX_MAIN_MGT_ID);

    MK_ERROR_e send_sig = _mk_Send_Signal(mgt_mb_handle,MK_SIGNAL_IPC_UPDATED);
    // Error Handling missing
    
    MK_HANDLE_t main_mb_handle = _mk_Get_Mailbox_Handle(MK_MAILBOX_MGT_MAIN_ID);
    _mk_Wait_Signal(main_mb_handle,MK_ENDLESS);
    ??


    return 0;
}*/
int send_command_main_mgt(int command){}