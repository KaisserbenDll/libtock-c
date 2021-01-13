#include "libvpp/vpp.h"
#include "libvpp/vff.h"



// This is the MGT Process/App 
int main(void) {

    // Initial FW Service functions Support 
    /*MGT_Response_Code respond = MGT_Store_Firmware_Header(fw_hdr1);
    MGT_Response_Code respond = MGT_Store_Firmware_Header(fw_hdr2);
    respond = MGT_Retrieve_Firmware_Header(fw_id);
    respond = MGT_Allocate_Firmware(fw_id);
    respond = MGT_Open_Process_SubMemoryPartition(fw_id,1);
    MK_ERROR_e err = _mk_Open_SubMemoryPartition(fw_id);
    void *ptr = _mk_Assign_SubMemoryPartition(0);
    uint8_t some_section[]={0xa3, 0x97, 0xa2, 0x55, 0x53, 0xbe, 0xf1, 0xfc, 0xf9,
    0x79, 0x6b, 0x52, 0x14, 0x13, 0xe9, 0xe2, 0x2d, 0x51, 0x8e, 0x1f, 0x56, 0x8, 0x57,
    0x27, 0xa7, 0x5, 0xd4, 0xd0, 0x52, 0x82, 0x77, 0x75, 0x1b, 0x99, 0x4a, 0xed, 0x58,
    0x3d, 0x6a, 0x52, 0x36, 0xd5, 0x24, 0x4a, 0x68, 0x8e, 0xad, 0x95, 0x5f, 0x3c, 0x35,
    0xb5, 0xc4, 0x8c, 0xdd, 0x6c, 0x11, 0x32, 0x3d, 0xe2, 0xb4, 0xb4, 0x59, 0xcf, 0xce,
    0x23, 0x3d, 0x27, 0xdf, 0xa7, 0xf9, 0x96, 0xfc, 0x1e, 0xe0, 0x66, 0x2c, 0xe, 0x7b,
    0x8c, 0xca, 0x30, 0x42, 0x8f, 0xbc, 0x9f, 0x7b, 0xce, 0xd1,};
    ptr = &some_section;
    write_segs(ptr);
    //write segments and pad 
    err= _mk_Commit_SubMemoryPartition();
    int khra = test();
*/    
    // Get Main and Mgt Mailboxes
    // MK_HANDLE_t mb_main_mgt = _mk_Get_Mailbox_Handle(MK_MAILBOX_MAIN_MGT_ID);
    // MK_HANDLE_t mb_mgt_main = _mk_Get_Mailbox_Handle(MK_MAILBOX_MGT_MAIN_ID);

    // Wait for MK_SIGNAL_IPC_UPDATED
     _mk_Wait_Signal(0x8001,0);
    // Access both Main and Mgt IPCs. This needs to be setup after wait_signal
    // MK_HANDLE_t main_mgt_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
    // MK_HANDLE_t mgt_main_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MGT_MAIN_ID);
    uint8_t*  ptr_main_mgt =  _mk_Get_Access_IPC(0x4001);
    uint8_t*  ptr_mgt_main = _mk_Get_Access_IPC(0x8001);


    while (true) {
    read_command_from_mgt(ptr_main_mgt,ptr_mgt_main);
    }
  return 0;
}
