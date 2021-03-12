#include "libvpp/vpp.h"
#include "libvpp/vff.h"
#include "libvpp/com.h"

extern uint8_t fw_hdr2[122];
extern uint8_t fw_id[16]; 
// This is the MAIN Process/App
// This is "The SYS APP" (extended permissions) 
int main(void) { 
    // Get IPCs
    MK_HANDLE_t main_mgt_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
    MK_HANDLE_t mgt_main_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MGT_MAIN_ID);
    uint8_t*  ptr_main_mgt = _mk_Get_Access_IPC(main_mgt_ipc_handle);
    uint8_t*  ptr_mgt_main =  _mk_Get_Access_IPC(mgt_main_ipc_handle);

    // 1) Send Store Header command
    send_from_main_to_mgt(ptr_main_mgt,fw_hdr2, MGT_Store_Firmware_Header_command
    ,122,0);
    
    // Read Response
    MGT_Response_Code mgt_response = ptr_mgt_main[0];

   if (mgt_response == MGT_ERROR_NONE){
    // 2) Send  Allocate command
    send_from_main_to_mgt(ptr_main_mgt,fw_id,MGT_Allocate_Firmware_command,16,0);
    }

    mgt_response = ptr_mgt_main[0];
    
    if (mgt_response == MGT_ERROR_NONE){
    // 3) Send  OpenSubMemory command
    send_from_main_to_mgt(ptr_main_mgt,fw_id
    ,MGT_Open_Process_SubMemoryPartition_command,16,0);
    }

    mgt_response = ptr_mgt_main[0];
    
    if (mgt_response == MGT_ERROR_NONE) {
    for (uint8_t i = 0; i < 3; i++){
     // 4) Open Sub Memory Partition 
    MK_ERROR_e kernel_error = _mk_Open_SubMemoryPartition(fw_id);
    // 5) Assign Sub Memory Partitions Code
    void* ptr = _mk_Assign_SubMemoryPartition(i);
    // write process segs
    uint8_t section[]={0xa3, 0x97, 0xa2, 0x55, 0x53, 0xbe, 0xf1, 0xfc, 0xf9,
    0x79, 0x6b, 0x52, 0x14, 0x13, 0xe9, 0xe2, 0x2d, 0x51, 0x8e, 0x1f, 0x56, 0x8, 0x57,
    0x27, 0xa7, 0x5, 0xd4, 0xd0, 0x52, 0x82, 0x77, 0x75, 0x1b, 0x99, 0x4a, 0xed, 0x58,
    0x3d, 0x6a, 0x52, 0x36, 0xd5, 0x24, 0x4a, 0x68, 0x8e, 0xad, 0x95, 0x5f, 0x3c, 0x35,
    0xb5, 0xc4, 0x8c, 0xdd, 0x6c, 0x11, 0x32, 0x3d, 0xe2, 0xb4, 0xb4, 0x59, 0xcf, 0xce,
    0x23, 0x3d, 0x27, 0xdf, 0xa7, 0xf9, 0x96, 0xfc, 0x1e, 0xe0, 0x66, 0x2c, 0xe, 0x7b,
    0x8c, 0xca, 0x30, 0x42, 0x8f, 0xbc, 0x9f, 0x7b, 0xce, 0xd1};
    ptr = &section;
    write_segs(ptr);

    // 6) Commit Sub Memory Partition CODE 
    kernel_error =_mk_Commit_SubMemoryPartition();

    // 7) Close Sub Memory Partition
    kernel_error = _mk_Close_SubMemoryPartition();
    }

    // 8) Send last command Close Process SubMemory Partition
    send_from_main_to_mgt(ptr_main_mgt,NULL
    ,MGT_Close_Process_SubMemoryPartition_command,0,0);
    mgt_response = ptr_mgt_main[0];
    }
    
    
     
 return 0;
}
