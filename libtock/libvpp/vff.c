#include "libvpp/vff.h"
#include "tock.h"
#include "libvpp/nvm.h"
size_t size_hdr = 122;
static void* root_ptr = NULL;

// firmware_header_data: the address of where the firmware header starts.
MGT_Response_Code MGT_Store_Firmware_Header(uint8_t* firmware_header_data){
    // 1. Parse Firmware Header
    // 2. Compare Firmware Header to capaibilites 

    // Send the firmware header buffer to the kernel and let him do the parsing
    // sizeof gives me always a 4 length. -_-
    // size_t size_hdr = my_sizeof(firmware_header_data);
   
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
    //write_nvm(firmware_header_data,size_hdr,offset_returned,size_hdr);



    // 5. b) Else Update Firmware_Header record.
        // Perform a write to NVM



    /*    struct source {
        int one;
    };
    struct source s = { 1 };
    void* ipc_ptr = malloc(20);
    memcpy(ipc_ptr, &s, sizeof(s));

    // 1. Parse Firmware Header
    struct source* myhdr = (struct source*) ipc_ptr;
    //printf("source %d", myhdr->one);

    */
    return MGT_ERROR_NONE;
}
MGT_Response_Code MGT_Retrieve_Firmware_Header(uint8_t* firmware_identifier){
    // First check if the Firmware id exists
    // Since size_of is buggy, i am hardcoding this.
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
     int offset = command(VFF_DRIVER_NUM, 3, 0, 0);*/
    uint8_t firmware_header_data[size_hdr];
    // Since the size of the VFF is predefined, it is hardcoded
    //read_nvm(firmware_header_data, size_hdr,offset,size_hdr);
    // the Firware Header should be read in firmware_header_data at this point.
    // return that pointer

    return MGT_ERROR_NONE;
}

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

int test(){
    // delay_ms(5000);
    int useless = command(VFF_DRIVER_NUM,2,0,0);
    return useless;
}

MK_ERROR_e _mk_Open_SubMemoryPartition(uint8_t* _uFirmwareID){
    // Argument should be changed to UUID_t. Then uncomment the next line
    //uint8_t* fw_id = &_uFirmwareID;
    MK_ERROR_e ret = (MK_ERROR_e) allow(VFF_DRIVER_NUM,4,(void*)_uFirmwareID,16);
    return ret;
}


void* _mk_Assign_SubMemoryPartition(MK_Index_t sub_Memory_Partition_Index){ 
    MK_ERROR_e ret = (MK_ERROR_e) command(VFF_DRIVER_NUM,4, sub_Memory_Partition_Index, 0);
    if (ret = 0 ) {
        return root_ptr;
    } else {
        return NULL; 
    }
}

void write_segs(void* ptr) {
    root_ptr = ptr;
}
MK_ERROR_e _mk_Commit_SubMemoryPartition(){
    MK_ERROR_e ret = (MK_ERROR_e) allow(VFF_DRIVER_NUM,5,root_ptr,100);
    return ret;
}

