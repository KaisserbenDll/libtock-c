#include "libvpp/vpp.h"

//__attribute__ ((unused)) static uint8_t readbuf[512];
// __attribute__ ((unused)) static uint8_t writebuf[512];

// This is the MAIN Process/App
// This is "The SYS APP" (extended permissions) 
int main(void) { 
   
    // Before accessing the IPC buff,handles are needed. 
     MK_HANDLE_t main_mgt_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
     MK_HANDLE_t mgt_main_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MGT_MAIN_ID);
    
    // Accessing both regions, one to map the command to be executed by the MGT Process
    // (MK_IPC_MAIN_MGT_ID) and one to read the response from (MK_IPC_MGT_MAIN_ID).
     void* __attribute__((aligned(256))) ptr_main_mgt = _mk_Get_Access_IPC(main_mgt_ipc_handle);
     void* __attribute__((aligned(256))) ptr_mgt_main =  _mk_Get_Access_IPC(mgt_main_ipc_handle);

    uint8_t arr[] ={0x00,0x11,0x22,0x33};
    ptr_main_mgt =&arr;

    /*Fill ptr_main_mgt with the data structure 
        "MGT service command code" + Data
        For example for MGT_Store_Firmware_Header the ptr_main_mgt should be filled:
        '00' + Firmware_Header_Data (Proc Descriptor+ IPC Descriptor+ ...)
    */
   // After  Filling the command to be executed, send the signal that the IPC got updated
     MK_HANDLE_t mb_main_mgt = _mk_Get_Mailbox_Handle(MK_MAILBOX_MAIN_MGT_ID);
     __attribute__ ((unused)) MK_ERROR_e send_sig_err= _mk_Send_Signal(mb_main_mgt,MK_SIGNAL_IPC_UPDATED);
    /*
    // Wait for the response from MGT Process on the MK_MAILBOX_MGT_MAIN_ID
    MK_HANDLE_t mb_mgt_main = _mk_Get_Mailbox_Handle(MK_MAILBOX_MGT_MAIN_ID);
    _mk_Wait_Signal(mb_mgt_main,0);*/
    /*Read the reponse in ptr_mgt_main*/





  

 return 0;
}
