#pragma once
#include <stdlib.h>
#include <string.h>
#include "tock.h"
#include "timer.h"
#include "libvpp/nvm.h"

//typedef unsigned __int128 uint128_t;

typedef long double uint128_t;

#ifdef __cplusplus
extern "C" {
#endif
// Definition of the VPP Kernel driver and Alarm Driver 
// used for syscalls.
#define VPP_DRIVER_NUM 0x90100
#define DRIVER_NUM_ALARM 0x0

// Testing variable for IPC length 
#define MK_IPC_MGT_LENGTH 256


// Index of an element in a typed array 
typedef uint16_t MK_Index_t;

typedef uint32_t MK_HANDLE_t;
typedef uint64_t MK_TIME_t;
// Identifiers need to be changed
typedef uint16_t MK_PROCESS_ID_u;
typedef uint16_t MK_IPC_ID_u;
typedef uint16_t MK_MAILBOX_ID_u;
typedef uint32_t MK_BITMAP_t;

typedef uint32_t MK_VRE_e;
//Memory address to a Process entry point 
typedef uint32_t PROCESS_Function_t;
// Unique Universal Identifier 
typedef uint128_t UUID_t;

typedef enum {
    MK_ERROR_NONE = 0, 
    MK_ERROR_UNKNOWN_UUID = 1,
    MK_ERROR_SEVERE = 2,
    MK_ERROR_ILLEGAL_PARAMETER = 3, 
    MK_ERROR_UNKNOWN_ID = 4,
    MK_ERROR_UNKNOWN_HANDLE = 5,
    MK_ERROR_UNKNOWN_PRIORITY = 6, 
    MK_ERROR_ACCESS_DENIED = 7,
    MK_ERROR_INTERNAL = 8,
    MK_ERROR_HANDLE_NOT_ACCESSED = 9, 
    MK_ERROR_GET_ERROR_HANDLE_NOT_A_PROCESS = 10,
    MK_ERROR_VENDOR_BASE = 32,
    MK_ERROR_MAX = 255,
} MK_ERROR_e ;
 

// System VPP Execution Domain 
#define MK_EXECUTION_DOMAIN_TYPE_VPP 0x2
// VPP Application Execution Domain
#define MK_EXECUTION_DOMAIN_TYPE_APP 0x1

// Definition of Cross-Execution Domain Composite Identifiers 
// Processes

//Mailboxes
#define MK_MAILBOX_COM_MAIN_ID (MK_EXECUTION_DOMAIN_TYPE_VPP<<14) | 0x0
#define MK_MAILBOX_MAIN_COM_ID (MK_EXECUTION_DOMAIN_TYPE_APP<<14) | 0x0

#define MK_MAILBOX_MGT_MAIN_ID (MK_EXECUTION_DOMAIN_TYPE_VPP<<14) | 0x1
#define MK_MAILBOX_MAIN_MGT_ID (MK_EXECUTION_DOMAIN_TYPE_APP<<14) | 0x1

//IPC
#define MK_IPC_MAIN_COM_ID (MK_EXECUTION_DOMAIN_TYPE_APP<<14) | 0x0
#define MK_IPC_COM_MAIN_ID (MK_EXECUTION_DOMAIN_TYPE_VPP<<14) | 0x0

#define MK_IPC_MAIN_MGT_ID (MK_EXECUTION_DOMAIN_TYPE_APP<<14) | 0x1
#define MK_IPC_MGT_MAIN_ID (MK_EXECUTION_DOMAIN_TYPE_VPP<<14) | 0x1

// Signal Identifiers 
#define MK_SIGNAL_DOMAIN_BASE_0 0x00000008
// The IPC Updated
#define MK_SIGNAL_IPC_UPDATED MK_SIGNAL_DOMAIN_BASE_0

typedef enum {
    FIRMWARE_SOFTWARE_TYPE_APP = 0x01,
    FIRMWARE_SOFTWARE_TYPE_VPP = 0x02,
    FIRMWARE_SOFTWARE_TYPE_SYSAPP = 0x04,  
    FIRMWARE_SOFTWARE_TYPE_LLOS = 0x08,
}VPP_FRW_TYPE_e; 

typedef enum{
    MK_SCHEDULING_TYPE_COLLABORATIVE = 0x01,
    MK_SCHEDULING_TYPE_PREEMPTIVE = 0x02,
}VPP_SCHEDULING_TYPE_e;


// Major and Minonr version of the VPP Firmware Format 
#define MK_FORMAT_VERSION 0b0100

// VPP Firmware Format
// Firmware Descriptor
struct fw_descr {
    // Firmware Identifier
    UUID_t m_xID;
    // Firmware Family Identifier
    UUID_t m_xFamilyID;
    // Length of the Firmware header
    uint16_t m_uHeaderLength;
    // Major and Minor version of the Firmware Format 
    uint16_t m_uVersionFormat;
    // Major and Minor version of the Firmware
    uint16_t m_uVersionFirmware;
    // Number of Process Descriptors
    uint8_t m_uProcessCount;
    // Number of Mailbox Descriptors
    uint8_t m_uMailboxCount;
    // Number of IPC Descriptors
    uint8_t m_uIPCCount;
    // Number of shared LIBrary Descriptors
    uint8_t m_uLIBCount;
    // Type of the Firmware 
    VPP_FRW_TYPE_e m_eFirmware_Software_Type;
    // Type of the Scheduling
    VPP_SCHEDULING_TYPE_e m_eSchedulingType;
};

// Process Descriptor
struct process_descr{
    // Offset within the CODE segment to compute a pointer to the Process entry point function
    PROCESS_Function_t m_pvProcessCode;
    // Length of the whole segement for CODE
    uint32_t m_uLength_Process_Code;
    // Length of the whole segement for CONSTANT data
    uint32_t m_uLength_Process_CONSTANTS;
    //Length of the whole segment for DATA
    uint32_t m_uLength_Process_DATA;
    // Length of the whole segment for NVM 
    uint32_t m_uLength_Process_NVM;
    // ORing of Mandatory Access Control for VRE
    MK_VRE_e m_eVRE;
    // Process Identifier
    MK_PROCESS_ID_u m_xID;
    // Identifier of the mailbox receiving signals
    MK_MAILBOX_ID_u m_xKernel_Mailbox;
    // Index of the Parent Process in the group of processes 
    MK_Index_t m_uParent_Process;
    // Size of the Stack (in bytes and multiple of 4)
    uint16_t m_uSizeStack; 
};

struct mailbox_descr {
    // Identifiers of the mailbox 
    MK_MAILBOX_ID_u m_xID;
    // Index of the owner/receiver Process in the group of processes
    MK_Index_t m_uIX_Owner; 
    // Index of the sender Process in the group of Processes
    MK_Index_t m_uIX_Sender;    
};
struct ipc_descr {
    // Identifiers of the IPC 
    MK_IPC_ID_u m_xID;
    // Length of the shared memory (in byte)
    uint16_t m_uLength_IPC; 
    // Index of the writer Process in the group of processes
    MK_Index_t m_uIX_Writer; 
    // Index of the reader Process in the group of Processes
    MK_Index_t m_uIX_Sender;    
};
struct vff_header{
    struct fw_descr fw_descriptor; 
    struct process_descr proc_descriptor;
    struct mailbox_descr mb_descriptor;
    struct ipc_descr  ipc_descriptor;
};

static const uint8_t command_code[13] = {
        0x00, 0x01 , 0x02, 0x03, 0x04, 0x05, 0x06,
        0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C
};

//struct fw_descr firmware_descriptor_test;
//void declare_firmware_decs(void);


/*
typedef enum {
    MGT_Store_Firmware_Header=0x00,
    MGT_Retrieve_Firmware_Header=0x01,
    MGT_Allocate_Firmware=0x02,
    MGT_Delete_Firmare=0x03,
    MGT_Enable_Firmware=0x04,
    MGT_Disable_Firmware=0x05,
    MGT_Is_Firmware_Enabled=0x06,
    MGT_Open_Process_SubMemoryPartition=0x07,
    MGT_Close_Process_SubMemoryPartition=0x08
}MGT_Command_Code;*/
typedef enum{
    MGT_ERROR_NONE=0x00,
    MGT_ERROR_ILLEGAL_PARAMETER=0x01,
    MGT_ERROR_INTERNAL=0x02, 
    MGT_ERROR_UNKNOWN_UUID=0x03,
    MGT_ERROR_COMMAND_NOK=0x04
}MGT_Response_Code;


// Gerneric Functions 
    // MK_BITMAP_t _mk_Get_Exception(MK_HANDLE_t _hProcess);
    MK_ERROR_e _mk_Get_Error(MK_HANDLE_t _hProcess);
    MK_TIME_t _mk_Get_Time(void);

// Process Management 
    MK_HANDLE_t _mk_Get_Process_Handle(MK_PROCESS_ID_u _eProcess_ID);
    //MK_ERROR_e _mk_Set_Process_Priority(MK_HANDLE_t _hProcess, MK_PROCESS_PRIORITY_e _xPriority);
    // MK_ERROR_e _mk_Suspend_Process(MK_HANDLE_t _hProcess);
    // MK_ERROR_e _mk_Resume_Process(MK_HANDLE_t _hProcess);
    //MK_ERROR_e _mk_Request_No_Preemption(uint32_t _uTime);
    // void_mk_Commit(void);
    // void_mk_RollBack(void);
    // void_mk_Yield(void);



// Mailbox Management 
//    MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID)
// Get a Mailbox Handle from a Mailbox Identifier 
MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID);
// Send a Signal to a specific mailbox
MK_ERROR_e _mk_Send_Signal(MK_HANDLE_t _hMailbox, MK_BITMAP_t _eSignal);
// Retrieve last Signal from Mailbox. Signals are cleared once read.
MK_BITMAP_t _mk_Get_Signal(MK_HANDLE_t _hMailbox);


void _mk_Wait_Signal(MK_HANDLE_t _hMailbox, uint32_t _utime);

// IPC Management
MK_HANDLE_t _mk_Get_IPC_Handle(MK_IPC_ID_u _eIPC_ID); 
void* _mk_Get_Access_IPC( MK_HANDLE_t _hIPC);

// Firmware Management ABI/API


// Firmware Management Service 

// The command code will be transfered through ipc and a use case
// will be used to call these functions accordingly
// 1) Firmware Header Management 
/*UUID_t MGT_Store_Firmware_Header(uint8_t* firmware_header_data);
MGT_Response_Code MGT_Retrieve_Firmware_Header(UUID_t firmware_identifier);

// 2) Firmware State Management
MGT_Response_Code MGT_Enable_Firmware(UUID_t firmware_identifier);
MGT_Response_Code MGT_Disable_Firmware(UUID_t firmware_identifier);
MGT_Response_Code MGT_Is_Firmware_Enabled(UUID_t firmware_identifier); 
MGT_Response_Code MGT_Delete_Firmare(UUID_t firmware_identifier);

// 3) Firmware Content Management
MGT_Response_Code MGT_Open_Process_SubMemoryPartition(UUID_t firmware_identifier,MK_Index_t index);
MGT_Response_Code MGT_Close_Process_SubMemoryPartition(void);
MGT_Response_Code MGT_Allocate_Firmware(UUID_t firmware_identifier);

*/

// Helper Functions for Firmware MGT service 
// Parse the first Byte from a pointer 
uint8_t Extract_Command_Code(void* ptr);

// Misc 
uint8_t* get_adress_nvm_memory(void);
//void init_mgt_proc(void);

#define MK_IPC_MGT_LENGTH 256
void* allow_ipc(void);

int test_tbf_head(void);

#ifdef __cplusplus
}
#endif