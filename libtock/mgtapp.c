#include "mgtapp.h"
/*#include "tock.h"


int recieve_command_mgt_main() {
    MK_HANDLE_t main_mb_handle = _mk_Get_Mailbox_Handle(MK_MAILBOX_MAIN_MGT_ID);
    
    _mk_Wait_Signal(main_mb_handle,MK_ENDLESS);

     MK_HANDLE_t main_ipc_handle =_mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
    
    int* shared_mem_ptr = _mk_Get_Access_IPC(main_ipc_handle);
    size_t len_command = strlen(command);
    memcpy(shared_mem_ptr,command,len_command);

    // based on the command data update the shared buffer 
    // case shared_mem_ptr 

    
 
   // missing is the response data sending through IPC
    MK_HANDLE_t main_mgt_mb_handle = _mk_Get_Mailbox_Handle(MK_MAILBOX_MGT_MAIN_ID);

    MK_ERROR_e send_sig = _mk_Send_Signal(mgt_mb_handle,MK_SIGNAL_IPC_UPDATED);

    // Error Handling missing
}*/

int recieve_command_mgt_main() {}

