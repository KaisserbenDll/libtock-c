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
/*
// firmware_header_data: the address of where the firmware header starts.
UUID_t MGT_Store_Firmware_Header(uint8_t* firmware_header_data){

    // 1. Parse Firmware Header
    struct fw_descr* fw_descr = (struct fw_descr*) firmware_header_data;
    // 2. Compare Firmware Header to capaibilites 

    // 3. Extract Firmware Identifier
    UUID_t myhdr_id = fw_descr->m_xID;
    // 4. Retrieve Firmware Header from MGT Process NVM, based on its provided Firmware Idenftifier
    // Perform a read from NVM 
     // Send command syscall to mgt_service to figure out if the identifier is stored
     // the mgt_service will send an offset != 0 if the 


    // 5. a )If Firmware Header not found, add a new Firmware Header, store provided 
    // Firmware Identifier as key to this record. The initial State should be Disabled.
    // Perofrm a write operation and tell the mgt_service of the new firmware header storage
    



    // 5. b) Else Update Firmware_Header record.
        // Perform a write to NVM



        struct source {
        int one;
    };
    struct source s = { 1 };
    void* ipc_ptr = malloc(20);
    memcpy(ipc_ptr, &s, sizeof(s));

    // 1. Parse Firmware Header
    struct source* myhdr = (struct source*) ipc_ptr;
    //printf("source %d", myhdr->one);

    
    return myhdr_id;
}*/
/*
void declare_firmware_decs() {
    firmware_descriptor_test.m_xID = 0x11112222 ;
    firmware_descriptor_test.m_xFamilyID=0x11112222;
    firmware_descriptor_test.m_uHeaderLength=0x90;
    firmware_descriptor_test.m_uVersionFormat=MK_FORMAT_VERSION;
    firmware_descriptor_test.m_uVersionFirmware=MK_FORMAT_VERSION;
    firmware_descriptor_test.m_uProcessCount=1;
    firmware_descriptor_test.m_uMailboxCount=1;
    firmware_descriptor_test.m_uIPCCount=1;
    firmware_descriptor_test.m_uLIBCount=0;
    firmware_descriptor_test.m_eFirmware_Software_Type=FIRMWARE_SOFTWARE_TYPE_SYSAPP;
    firmware_descriptor_test.m_eSchedulingType=MK_SCHEDULING_TYPE_COLLABORATIVE;

}*/

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