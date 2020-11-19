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
void* mk__Get_ACcess (MK_HANDLE_t _HIPC) {

    len = getIPClen(_hIPC);
    // statisch allokieren
    char shared_memory[len] ; 
    allow(VPP_DRIVER_NUM,_HIPC,shared_memory, len);
    return shared_memory 
}*/


void* Share(__attribute__ ((unused)) MK_HANDLE_t _hIPC) {
    //int size_ipc = command(VPP_DRIVER_NUM,20,_hIPC,0);
    char* shared_buffer = (char*) malloc (MK_IPC_MGT_LENGTH);
    // Registering the share from buffer located in the other app.
    // The buff is declared in the header file as extern variable, However
    // it needs to be defined in the writer process that is registering this syscall
    // + 
    // Exposing the share slice to whoever called this function
    // This where the actual access permission is issued.
   __attribute__ ((unused)) int res = allow(VPP_DRIVER_NUM, 0, share, MK_IPC_MGT_LENGTH);

    //memcpy(shared_buffer,share,MK_IPC_MGT_LENGTH);
    return (void*) shared_buffer; 
}

int register_share(void* buffer) {
        
        return allow(VPP_DRIVER_NUM, 0x8001, buffer, 128);
        //return *buf ;
}
/*
void* _mk_Get_IPC_Access(MK_HANDLE_t _hIPC){

     allow(VPP_DRIVER_NUM, _hIPC, shared_buffer, 128);
    return *shared_buffer;
}
int some_subscribe_test(MK_HANDLE_t _hIPC, subscribe_cb callback, void *ud){
  return subscribe(VPP_DRIVER_NUM, _hIPC, callback, ud);
}*/
/*
static void register_share_cb(int a ,int b,int c ,void* buffer){
    register_share(buffer);
}*/
