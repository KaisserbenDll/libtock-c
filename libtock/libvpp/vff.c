#include "libvpp/vff.h"
#include "tock.h"
#include "libvpp/nvm.h"
size_t size_hdr = 122;
static void* root_ptr = NULL;
// Firmware Header used for Testing 
 __attribute__ ((unused)) uint8_t fw_hdr1[90]={
    0xa3, 0x97, 0xa2, 0x55, 0x53, 0xbe, 0xf1, 0xfc,
    0xf9, 0x79, 0x6b, 0x52, 0x14, 0x13, 0xe9, 0xe2,
    0x2d, 0x51, 0x8e, 0x1f, 0x56, 0x8, 0x57, 0x27, 
    0xa7, 0x5, 0xd4, 0xd0, 0x52, 0x82, 0x77,0x75, 
    0x1b, 0x99, 
    0x4a, 0xed, 
    0x58, 0x3d, 
    0x01, // # Processes
    0x01, // # Mailboxes
    0x01, // # IPC
    0x00,  
    0x01, // FW_SW Type
    0x01, // Scheduling Type
    0x00, 0x00, 0x00, 0x00,  // Offset  
    0x00, 0x00, 0x10, 0x00, // CODE size
    0x00, 0x00, 0x10, 0x00, // CONSTANT size
    0x00, 0x00, 0x10, 0x00, // DATA size
    0x00, 0x00, 0x10, 0x00, // NVM size
    0xce, 0x23, 0x3d, 0x27, 
    0x40, 0x02,  // Proc ID  
    0x40, 0x02,  // MB ID recieving from Kernel 
    0x00, 0x00, // Index Parent Process 
    0x04, 0x00, // Stack Size
    0x2c, 0xe0, // MB ID
    0x7b, 0x8c,
    0xca, 0x30, 
    0x42, 0x8f, // IPC ID
    0xbc, 0x9f, 
    0x7b, 0xce, 
    0xd1, 0xb8};
// Another Firmware Header used for Testing 
__attribute__ ((unused))  uint8_t fw_hdr2[122]={
    0xde, 0xad, 0xbe, 0xef, 0xda, 0xad, 0xff, 0xff,
    0xde, 0xad, 0xbe, 0xef, 0xda, 0xad, 0xff, 0xff,
    0xde, 0xad, 0xbe, 0xef, 0xda, 0xad, 0xff, 0xff,
    0xde, 0xad, 0xbe, 0xef, 0xda, 0xad, 0xff, 0xff,
    0x00, 0x78, 
    0x00, 0x04, 
    0x00, 0x04, 
    0x02, // # Processes
    0x01, // # Mailboxes
    0x01, // # IPC
    0x00,  
    0x01, // FW_SW Type
    0x01, // Scheduling Type
    // # Proc 1
    0x00, 0x00, 0x00, 0x00,  // Offset  
    0x00, 0x00, 0x00, 0xFF, // CODE size 0xF4
    0x00, 0x00, 0x00, 0x54, // CONSTANT size 0x64
    0x00, 0x00, 0x00, 0x89, // DATA size 0x96
    0x00, 0x00, 0x00, 0x46, // NVM size 0x62
    0xce, 0x23, 0x3d, 0x27, 
    0x40, 0x02,  // Proc ID  
    0x40, 0x02,  // MB ID recieving from Kernel 
    0x00, 0x00, // Index Parent Process 
    0x00, 0x10, // Stack Size
    // # Proc 2
    0x00, 0x00, 0x00, 0x00,  // Offset  
    0x00, 0x00, 0x00, 0xC8, // CODE size
    0x00, 0x00, 0x00, 0x28, // CONSTANT size
    0x00, 0x00, 0x00, 0x6E, // DATA size
    0x00, 0x00, 0x00, 0x1E, // NVM size
    0xce, 0x23, 0x3d, 0x27, 
    0x40, 0x02,  // Proc ID  
    0x40, 0x02,  // MB ID recieving from Kernel 
    0x00, 0x00, // Index Parent Process 
    0x00, 0x10, // Stack Size
    0x2c, 0xe0, // MB ID
    0x7b, 0x8c,
    0xca, 0x30, 
    0x42, 0x8f, // IPC ID
    0xbc, 0x9f, 
    0x7b, 0xce, 
    0xd1, 0xb8};

uint8_t fw_id[16]={
    0xde, 0xad, 0xbe, 0xef, 0xda, 0xad, 0xff, 0xff,
    0xde, 0xad, 0xbe, 0xef, 0xda, 0xad, 0xff, 0xff};

// 1) Firmware Header Management
MGT_Response_Code MGT_Store_Firmware_Header(uint8_t* firmware_header_data){
    // 1. Parse Firmware Header
    // 2. Compare Firmware Header to capaibilites 

    // Send the firmware header buffer to the kernel and let him do the parsing
    // sizeof gives me always a 4 length. -_-
    // size_t size_hdr = my_sizeof(firmware_header_data);

    // uint8_t fw_hdr_data[122] = {0};
    // memcpy(fw_hdr_data,firmware_header_data,122);

    int return_value = allow(VFF_DRIVER_NUM, 
                        0, 
                        (void*) firmware_header_data,
                        size_hdr);
    // Handle the return value and extract the offset 
    uint8_t offset_returned = (return_value >> 16);
    uint8_t ret = return_value & 0xFF;
     if (ret != 0x00) {
        // The Kernel failed to parse the Header buffer
        return ret;
     };

     /*
    // 4. Retrieve Firmware Header from MGT Process NVM, based on its provided Firmware Idenftifier
    // Perform a read from NVM 
     // Send command syscall to mgt_service to figure out if the identifier is stored
     // the mgt_service will send an offset != 0 if the 
    
    // SKIP THIS FOR NOW 

    // 5. a )If Firmware Header not found, add a new Firmware Header, store provided 
    // Firmware Identifier as key to this record. The initial State should be Disabled.
    // Perofrm a write operation and tell the mgt_service of the new firmware header storage

    // Inform the kernel that the firmware header that we parsed shall be stored 
    // with a certain offset
   /* ret = command (VFF_DRIVER_NUM,1,global_offset,0);
    if (ret != 0x00) {
        // This operation should not fail, but in case it does it's an 
        // internal error. 
        return ret;
    };*/
    // After informing the kernel, we perform a write operation in the NVM.
    // write_nvm(fw_hdr_data,size_hdr,offset_returned,size_hdr);



    // 5. b) Else Update Firmware_Header record.
        // Perform a write to NVM

    return MGT_ERROR_NONE;
}
MGT_Response_Code MGT_Retrieve_Firmware_Header(uint8_t* firmware_identifier){
    // First check if the Firmware id exists
    // Since sizeof is buggy, i am hardcoding this.
    size_t size_id = 16; 
     int ret_value = allow(VFF_DRIVER_NUM, 
                                1,
                                (void*) firmware_identifier,
                                size_id);
     uint16_t ret = ret_value & 0xFF;
     uint16_t offset = (ret_value >> 16);
     // A value for the length of the read op should be added.
     if (ret != 0x00) {
        // The Kernel failed to parse the Header buffer
        return ret;
     };

     /*// Second, ask the kernel, from which offset should the FwHdr should be read
     int offset = command(VFF_DRIVER_NUM, 4, 0, 0);*/
    uint8_t firmware_header_data[size_hdr];
    // Since the size of the VFF is predefined, it is hardcoded
    read_nvm(firmware_header_data, size_hdr,offset,size_hdr);
    // the Firware Header should be read in firmware_header_data at this point.
    // return that pointer

    return MGT_ERROR_NONE;
}

// 2) Firmware State Management
/*MGT_Response_Code MGT_Enable_Firmware(UUID_t firmware_identifier){}
MGT_Response_Code MGT_Disable_Firmware(UUID_t firmware_identifier){}
MGT_Response_Code MGT_Is_Firmware_Enabled(UUID_t firmware_identifier){} 
MGT_Response_Code MGT_Delete_Firmare(UUID_t firmware_identifier){}
*/
// 3) Firmware Content Management,
MGT_Response_Code MGT_Allocate_Firmware(uint8_t* firmware_identifier){
    // Check if firmware exists. If it does, memory offsets and values will be 
    // setup but not yet copied.
    // Since size_of is buggy, i am hardcoding this.
    size_t size_id = 16; 
    int ret = allow(VFF_DRIVER_NUM, 2, (void*) firmware_identifier, size_id);

    return (MGT_Response_Code) ret;
}

MGT_Response_Code MGT_Open_Process_SubMemoryPartition(uint8_t* firmware_identifier,MK_Index_t index){
    
    size_t size_id = 16; 
    uint32_t arg = (index << 8) | 3 ;
    int ret = allow(VFF_DRIVER_NUM, arg, (void*) firmware_identifier, size_id);

    return (MGT_Response_Code) ret;
}


MGT_Response_Code MGT_Close_Process_SubMemoryPartition(void){
    MGT_Response_Code ret = command(VFF_DRIVER_NUM,3, 0, 0);
    return ret;
}

// Kernel API/ABI
MK_ERROR_e _mk_Open_SubMemoryPartition(uint8_t* _uFirmwareID){
    // Argument should be changed to UUID_t. Then uncomment the next line
    //uint8_t* fw_id = &_uFirmwareID;
    MK_ERROR_e ret = allow(VFF_DRIVER_NUM,4,(void*)_uFirmwareID,16);
    return ret;
}

void* _mk_Assign_SubMemoryPartition(MK_Index_t sub_Memory_Partition_Index){ 
    MK_ERROR_e ret = command(VFF_DRIVER_NUM,1, sub_Memory_Partition_Index, 0);
    if (ret == 0 ) {
        root_ptr = NULL; 
        return root_ptr;
    } else {
        return NULL; 
    }
}

MK_ERROR_e _mk_Commit_SubMemoryPartition(void){
    MK_ERROR_e ret = allow(VFF_DRIVER_NUM,5,root_ptr,89);
    return ret;
}

MK_ERROR_e _mk_Close_SubMemoryPartition(void){
    MK_ERROR_e ret = command(VFF_DRIVER_NUM,2, 0, 0);
    return ret;
}

// Helper Functions
/*void write_segs(uint8_t* section) {
    root_ptr = &section;
}*/
void write_segs(void* ptr) {
    root_ptr = ptr;
}
// Read the first byte of the command_data and interpret the command. Based on that command, 
// an operation in the kernel is executed.
MGT_Response_Code Read_Execute_Command(uint8_t* command_data){
    uint8_t command = command_data[0];
    command_data+=1;
    MGT_Response_Code response = MGT_ERROR_COMMAND_NOK; 
    switch (command)
    {
    case MGT_Store_Firmware_Header_command:
        response = MGT_Store_Firmware_Header(command_data);
        break;
    case MGT_Allocate_Firmware_command:
        response = MGT_Allocate_Firmware(command_data);
        break;   
    case MGT_Open_Process_SubMemoryPartition_command: ;
        uint8_t* fw_id_tmp = command_data;
        command_data+=16;
        MK_Index_t index_tmp = command_data[0];
        command_data-=16;
        response = MGT_Open_Process_SubMemoryPartition(fw_id_tmp,index_tmp);
        break;  
    case MGT_Close_Process_SubMemoryPartition_command:
        response = MGT_Close_Process_SubMemoryPartition();
        break;         
    default:
        break;
    }
    return response;
}

// Sends a command to be executed following a certain format expected from the MGT app. 
// Map it on the IPC (write_buf) afterwards.
void send_from_main_to_mgt(uint8_t* write_buf,
                            uint8_t*buf, 
                            uint8_t command,
                            size_t size,
                            uint8_t index) {
    memset(write_buf,0,MK_IPC_MGT_LENGTH);
    write_buf[0]= command;
    write_buf+=1;

    switch (command)
    {
    case MGT_Store_Firmware_Header_command:
    case MGT_Allocate_Firmware_command:
            memcpy(write_buf,buf,size);
        break;
    case MGT_Open_Process_SubMemoryPartition_command:
            memcpy(write_buf,buf,size);
            write_buf+=size;
            write_buf[0]= index;
            write_buf -=size;
            break;
    case MGT_Close_Process_SubMemoryPartition_command:
            break;
    default:
        break;
    }                        
    write_buf-=1;

    MK_ERROR_e send_sig_err= _mk_Send_Signal(0x8001,MK_SIGNAL_IPC_UPDATED);
    // Wait for response from MGT     
    _mk_Wait_Signal(0x4001,0);
}

// This function reads a command from the IPC (read_buf), executes it and maps the returned reponse 
// on the IPC (write_buf). Afterwards, it waits for a signal to be received on its Mailbox
void read_command_from_mgt(uint8_t* read_buf,
                           uint8_t* write_buf){
    // 0x8001 and 0x4001 are the IDs of the mailboxes
    // These are hardcoded. These should be retrieved handles however.
    MGT_Response_Code response = Read_Execute_Command(read_buf);
    write_buf[0] = response;
    MK_ERROR_e send_sig_err= _mk_Send_Signal(0x4001,MK_SIGNAL_IPC_UPDATED);
    // Wait for MK_SIGNAL_IPC_UPDATED
    _mk_Wait_Signal(0x8001,0);

}
