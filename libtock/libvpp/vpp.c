#include "libvpp/vpp.h"
#include "tock.h"


MK_ERROR_e _mk_Get_Error(MK_HANDLE_t _hProcess){
    return command(VPP_DRIVER_NUM, 100, _hProcess, 0);
 }

MK_TIME_t _mk_Get_Time(void){
    return (MK_TIME_t) command(DRIVER_NUM_ALARM,2,0,0);
};

MK_HANDLE_t _mk_Get_Process_Handle(MK_PROCESS_ID_u _eProcess_ID){
    return command(VPP_DRIVER_NUM, 1, _eProcess_ID, 0);
}



MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID){
    return command(VPP_DRIVER_NUM, 5, _eMailboxID, 0);

}
MK_ERROR_e _mk_Send_Signal(MK_HANDLE_t _hMailbox, MK_BITMAP_t _eSignal){
    return command(VPP_DRIVER_NUM,6,_hMailbox,_eSignal);
}
MK_BITMAP_t _mk_Get_Signal(MK_HANDLE_t _hMailbox){
    return command(VPP_DRIVER_NUM,7,_hMailbox,0);
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

const char* register_share(void) {
        //char* shared_memory[128];
        __attribute__ ((unused)) int ret =  allow(VPP_DRIVER_NUM, 0x8001, buf, 128);
        return *buf ;
}

int some_subscribe_test(MK_HANDLE_t _hIPC, subscribe_cb callback, void *ud){
  return subscribe(VPP_DRIVER_NUM, _hIPC, callback, ud);
}
