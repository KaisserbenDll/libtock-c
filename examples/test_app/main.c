#include "libvpp/vpp.h"
#include "libvpp/vff.h"



// This is the MGT Process/App 
int main(void) {
    // Get Main and Mgt Mailboxes
    // MK_HANDLE_t mb_main_mgt = _mk_Get_Mailbox_Handle(MK_MAILBOX_MAIN_MGT_ID);
    // MK_HANDLE_t mb_mgt_main = _mk_Get_Mailbox_Handle(MK_MAILBOX_MGT_MAIN_ID);
    
    // Wait for MK_SIGNAL_IPC_UPDATED
     _mk_Wait_Signal(0x8001,0);

    MK_ERROR_e send_err= _mk_Send_Signal(0x4001,MK_SIGNAL_IPC_UPDATED);
     _mk_Wait_Signal(0x8001,0);

    // Access both Main and Mgt IPCs. This needs to be setup after wait_signal
    // MK_HANDLE_t main_mgt_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
    // MK_HANDLE_t mgt_main_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MGT_MAIN_ID);
   // uint8_t*  ptr_main_mgt =  _mk_Get_Access_IPC(0x4001);
    //uint8_t*  ptr_mgt_main = _mk_Get_Access_IPC(0x8001);


   /* while (true) {
    read_command_from_mgt(ptr_main_mgt,ptr_mgt_main);
    }*/
  return 0;
}
