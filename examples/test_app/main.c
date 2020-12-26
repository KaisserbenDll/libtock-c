#include "libvpp/vpp.h"
#include "libvpp/vff.h"

//__attribute__ ((unused))static uint8_t readbuf[512];
//__attribute__ ((unused))static uint8_t writebuf[512];

// This is the MGT Process/App 
int main(void) {
    //printf("Hello");

    MGT_Response_Code respond = MGT_Store_Firmware_Header(fw_hdr1);
    respond = MGT_Store_Firmware_Header(fw_hdr2);
     respond = MGT_Retrieve_Firmware_Header(fw_id);
    // respond = MGT_Allocate_Firmware(fw_id);

    /*
    uint8_t firmware_data[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

    UUID_t id =  MGT_Store_Firmware_Header(firmware_data);
    printf("%Lf", id);

    */
    //test_tbf_head();
    /*
    // At this point the IPC has not been configured yet for the MAIN App 
    // That is why we wait for the signal first and then have access to the IPC.
    MK_HANDLE_t mb_main_mgt = _mk_Get_Mailbox_Handle(MK_MAILBOX_MAIN_MGT_ID);
     _mk_Wait_Signal(mb_main_mgt,0);
    // At this point we have the configured/shared MGT IPC and updated so 
    //we can continue reading the response and processing it  

    // Before accessing the IPC buff between processes, we need to get 
    // the handle of both of them. Even the MGT app needs to request the access 
    // from the kernel to get the access over its own IPC.(Same applies to MAIN)
    MK_HANDLE_t main_mgt_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
    MK_HANDLE_t mgt_main_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MGT_MAIN_ID);
    
    // Accessing both regions, one to read the command requested by the MAIN Process
    // (MK_IPC_MAIN_MGT_ID) and one to send the response data (MK_IPC_MGT_MAIN_ID).
     void* __attribute__((aligned(256))) ptr_main_mgt =  _mk_Get_Access_IPC(main_mgt_ipc_handle);
     void* __attribute__((aligned(256))) ptr_mgt_main = _mk_Get_Access_IPC(mgt_main_ipc_handle);
    printf("ptr addr %p",ptr_main_mgt);
    printf("ptr addr %p",ptr_main_mgt);
    printf("ptr addr %p",ptr_main_mgt);
    printf("ptr addr %p",ptr_main_mgt);
    printf("ptr_mgt_main %u\n",* (uint8_t*)ptr_mgt_main);
*/
    // printf("ptr addr %u",*ptr_main_mgt);

    // Read the command from ptr_main_mgt and Send the reponse to ptr_mgt_main
    // First step is to extract the command code.
    //uint8_t command_code_t = Extract_Command_Code(ptr_main_mgt);
    //    printf("command request %x\n", command_code_t);
    /*if (*ptr_main_mgt==10) {
           printf("OK\n");

    }*/


    //printf("command request %d\n", *ptr_mgt_main);


    /*printf("command_code %u", command_code);
    ptr_main_mgt+=1;
    // parse the Firmware Header and extract the Firmware ID 
     switch (command_code_t) {
        case 00:    
            MGT_Store_Firmware_Header(ptr_main_mgt);
            break;
        case 0x01:

            MGT_Retrieve_Firmware_Header(firmware_descriptor_test.m_xID);
            break;
        case 0x02:
            MGT_Allocate_Firmware(firmware_descriptor_test.m_xID);
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
        case 0x09:
        case 0x0a:
        case 0x0b:
        case 0x0c:

    } */



    /*Processing each command and Responding differently */
    //MK_HANDLE_t mb_mgt_main = _mk_Get_Mailbox_Handle(MK_MAILBOX_MGT_MAIN_ID);
    // __attribute__ ((unused)) MK_ERROR_e send_sig_err= _mk_Send_Signal(mb_mgt_main,MK_SIGNAL_IPC_UPDATED);

  return 0;
}
