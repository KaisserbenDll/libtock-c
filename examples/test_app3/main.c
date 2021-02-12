#include "libvpp/vpp.h"
#include "libvpp/com.h"
// This is the COM Process/App 
int main(void) {
    // Get Mailboxes.
    // MK_HANDLE_t mb_main_com = _mk_Get_Mailbox_Handle(MK_MAILBOX_MAIN_COM_ID);
    // MK_HANDLE_t mb_mgt_main = _mk_Get_Mailbox_Handle(MK_MAILBOX_COM_MAIN_ID);
    // Get IPCs
    // MK_HANDLE_t main_com_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MAIN_COM_ID);
    // MK_HANDLE_t com_main_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_COM_MAIN_ID);
    _mk_Wait_Signal(0x8000,0);
    uint8_t*  ptr_main_com = _mk_Get_Access_IPC(0x4000);
    uint8_t*  ptr_com_main =  _mk_Get_Access_IPC(0x8000);

    // Perform Read Operation
    struct return_struct read_struct = *(struct return_struct*) ptr_main_com ;  
    uint32_t read_index = ((read_struct.m_Write_IN - 1) % read_struct.m_Size_In) ; 
    uint16_t read_data_chunk =  ((uint16_t*) read_struct.m_Buff_IN)[read_index] ;
    read_struct.m_Read_OUT +=1;


    struct parameters_struct param ;
    param.m_MTU_OUT = read_struct.m_MTU_IN; 
    param.m_Size_OUT = read_struct.m_Size_In ; 
    param.m_Read_IN = read_struct.m_Read_OUT;  
    param.m_Write_OUT = read_struct.m_Write_IN;
    param.m_Buff_OUT = read_struct.m_Buff_IN;


    // Perform Write Operation
    ((uint16_t*) param.m_Buff_OUT)[param.m_Write_OUT]=0xEE ;

    //(*(uint16_t*)param.m_Buff_OUT)[param.m_Write_OUT] = 0xEE;    
    param.m_Write_OUT+=1;
    memcpy(ptr_com_main,&param,sizeof(param));
    int retur =allow(VPP_DRIVER_NUM,2,ptr_com_main,30);

   // Send MK_IPC_UPDATED
     MK_ERROR_e send_sig_err= _mk_Send_Signal(0x4000,MK_SIGNAL_IPC_UPDATED);
    _mk_Wait_Signal(0x8000,0);  

  

  return 0;
}
