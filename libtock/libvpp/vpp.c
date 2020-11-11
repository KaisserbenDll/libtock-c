#include "libvpp/vpp.h"
#include "tock.h"


MK_ERROR_e _mk_Get_Error(MK_HANDLE_t _hProcess){
    return command(VPP_DRIVER_NUM, 100, _hProcess, 0);
 }
MK_HANDLE_t _mk_Get_Process_Handle(MK_PROCESS_ID_u _eProcess_ID){
    return command(VPP_DRIVER_NUM, 1, _eProcess_ID, 0);
}
/*
void* _mk_Get_Access_IPC (MK_HANDLE_t _hIPC) {
    // i am sharing an appslice and putting it in the data.shared_data struct
    int ret =  allow(VPP_DRIVER_NUM, _hIPC, _shared_memory, 64);
    return (void*) ret ;
}*/
// Another function should call 
/*
ipc_03[SIZE_OF_MGT_MAIN_IPC] ;
void* Share_Slice (MK_HANDLE_t _hIPC) {
    return allow(VPP_DRIVER_NUM,_hIPC, ipc_03,64);
    return hello_test 
}
addres = _mk_Get_Access_IP(0x8001) ;

void* mk__Get_ACcess (MK_HANDLE_t _HIPC) {

    len = getIPClen(_hIPC);
    // statisch allokieren
    char shared_memory[len] ; 
    allow(VPP_DRIVER_NUM,_HIPC,shared_memory, len);
    return shared_memory 
}*/