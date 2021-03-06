#include "libvpp/vpp.h"
#include "libvpp/vff.h"
#include "libvpp/com.h"

extern uint8_t fw_hdr2[122];
extern uint8_t fw_id[16]; 
// This is the MAIN Process/App
// This is "The SYS APP" (extended permissions) 
int main(void) { 
    // Get Mailboxes.
    // MK_HANDLE_t mb_main_mgt = _mk_Get_Mailbox_Handle(MK_MAILBOX_MAIN_MGT_ID);
    // MK_HANDLE_t mb_mgt_main = _mk_Get_Mailbox_Handle(MK_MAILBOX_MGT_MAIN_ID);
    // Get IPCs
    // MK_HANDLE_t main_mgt_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
    // MK_HANDLE_t mgt_main_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MGT_MAIN_ID);
    //uint8_t*  ptr_main_mgt = _mk_Get_Access_IPC(0x4001);
   // uint8_t*  ptr_mgt_main =  _mk_Get_Access_IPC(0x8001);
    uint8_t*  ptr_main_com = _mk_Get_Access_IPC(0x4000);
    uint8_t*  ptr_com_main =  _mk_Get_Access_IPC(0x8000);

  // Perform a Write FIFO OUT Operation
  struct parameters_struct param ;
  param.m_MTU_OUT = m_MTU_OUT_init; 
  param.m_Size_OUT = m_Size_OUT_init ; 
  param.m_Read_IN = m_Read_IN_init;  
  param.m_Write_OUT = m_Write_OUT_init;
  uint16_t* buff_out[m_Size_OUT_init] = {0}; 
  param.m_Buff_OUT = (void*) buff_out;
  // Write data chunk in buff_out 
  buff_out[param.m_Write_OUT] = 0xFF ; 
  param.m_Write_OUT+=1;
  // Map the data structure to IPC 
  memcpy(ptr_main_com,&param,sizeof(param));
    int retur =allow(VPP_DRIVER_NUM,2,ptr_main_com,30);
  // Send MK_IPC_UPDATED
  MK_ERROR_e send_sig_err= _mk_Send_Signal(0x8000,MK_SIGNAL_IPC_UPDATED);
  _mk_Wait_Signal(0x4000,0);

    // Perform a Read FIFO IN Operation
    struct return_struct read_struct = *(struct return_struct*) ptr_com_main ;  
    uint32_t read_index = ((read_struct.m_Write_IN - 1) % read_struct.m_Size_In) ; 
    uint16_t read_data_chunk =  ((uint16_t*) read_struct.m_Buff_IN)[read_index] ;
    read_struct.m_Read_OUT +=1;

    struct parameters_struct param1 ;
    param1.m_MTU_OUT = read_struct.m_MTU_IN; 
    param1.m_Size_OUT = read_struct.m_Size_In ; 
    param1.m_Read_IN = read_struct.m_Read_OUT;  
    param1.m_Write_OUT = read_struct.m_Write_IN;
    param1.m_Buff_OUT = read_struct.m_Buff_IN;
    memcpy(ptr_main_com,&param1,sizeof(param1));

    retur = allow(VPP_DRIVER_NUM,2,ptr_main_com,30);

    
    // Definition of FIFO_IN
    /*struct return_struct read_response;
    uint16_t* buff_in[m_Size_IN_init] = {0}; 
    read_response.m_MTU_IN  = m_MTU_IN_init ; 
    read_response.m_Size_In = m_Size_IN_init; 
    read_response.m_Read_OUT= m_Read_OUT_init;
    read_response.m_Write_IN= m_Write_IN_init;
    read_response.m_Buff_IN= (void*) buff_in;*/


    

    //

     
 return 0;
}
