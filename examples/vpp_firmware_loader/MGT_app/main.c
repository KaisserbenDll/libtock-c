#include "libvpp/vpp.h"
#include "libvpp/vff.h"

// This is the MGT Process/App 
int main(void) {
  
    _mk_Wait_Signal(0x8001,0);
    // Access both Main and Mgt IPCs. This needs to be setup after wait_signal
    MK_HANDLE_t main_mgt_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MAIN_MGT_ID);
    MK_HANDLE_t mgt_main_ipc_handle = _mk_Get_IPC_Handle(MK_IPC_MGT_MAIN_ID);
    uint8_t*  ptr_main_mgt =  _mk_Get_Access_IPC(main_mgt_ipc_handle);
    uint8_t*  ptr_mgt_main = _mk_Get_Access_IPC(mgt_main_ipc_handle);
    
    // Enter endless loop to recieve commands from SysApp, handle them and then map
    // response on IPC. 
    while (true) {
    read_command_from_mgt(ptr_main_mgt,ptr_mgt_main);
    }
  return 0;
}
