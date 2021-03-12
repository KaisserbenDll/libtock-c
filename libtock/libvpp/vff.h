#pragma once
#include "libvpp/vpp.h"

#define VFF_DRIVER_NUM 0x90200
#define SIZE_VFF_HEADER 90
#define my_sizeof(x) ((char *)(&x + 1) - (char *)&x)

// MGT Service Commands
#define  MGT_Store_Firmware_Header_command 0x00
#define  MGT_Retrieve_Firmware_Header_command 0x01
#define MGT_Allocate_Firmware_command 0x02
#define MGT_Open_Process_SubMemoryPartition_command 0x07
#define MGT_Close_Process_SubMemoryPartition_command 0x08

// Index of Sub Memory Partition
# define SubMemPart_CODE_i 0 
# define SubMemPart_CONSTANT_i 1 
# define SubMemPart_NVM_i 2

typedef enum{
    MGT_ERROR_NONE=0x00,
    MGT_ERROR_ILLEGAL_PARAMETER=0x01,
    MGT_ERROR_INTERNAL=0x02, 
    MGT_ERROR_UNKNOWN_UUID=0x03,
    MGT_ERROR_COMMAND_NOK=0x04
}MGT_Response_Code;

// 1) Firmware Header Management 
MGT_Response_Code MGT_Store_Firmware_Header(uint8_t* firmware_header_data);
MGT_Response_Code MGT_Retrieve_Firmware_Header(uint8_t* firmware_identifier);

// 2) Firmware State Management
MGT_Response_Code MGT_Enable_Firmware(UUID_t firmware_identifier);
MGT_Response_Code MGT_Disable_Firmware(UUID_t firmware_identifier);
MGT_Response_Code MGT_Is_Firmware_Enabled(UUID_t firmware_identifier); 
MGT_Response_Code MGT_Delete_Firmare(UUID_t firmware_identifier);

// 3) Firmware Content Management
MGT_Response_Code MGT_Open_Process_SubMemoryPartition(uint8_t* firmware_identifier,MK_Index_t index);
MGT_Response_Code MGT_Close_Process_SubMemoryPartition(void);
MGT_Response_Code MGT_Allocate_Firmware(uint8_t* firmware_identifier);

// 4) Firmware Kernel Management
MK_ERROR_e _mk_Open_SubMemoryPartition(uint8_t* _uFirmwareID);
void* _mk_Assign_SubMemoryPartition(MK_Index_t sub_Memory_Partition_Index);
void write_segs(void* ptr);
MK_ERROR_e _mk_Commit_SubMemoryPartition(void);
MK_ERROR_e _mk_Close_SubMemoryPartition(void);

// Helper Functions
MGT_Response_Code Read_Command(uint8_t* command_data);
void send_from_main_to_mgt( uint8_t* write_buf,
                            uint8_t*buf, 
                            uint8_t command, 
                            size_t size, 
                            uint8_t index);
void read_command_from_mgt(uint8_t* read_buf, uint8_t* write_buf);