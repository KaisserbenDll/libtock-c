#include "processmanager.h"
#include "tock.h"

//MK_HANDLE_t _mk_Get_Process_Handle(MK_PROCESS_ID_u _eProcess_ID){
//    return command(DRIVER_NUM_PM, 4, _eProcess_ID, 0);
//}

MK_ERROR_e _mk_Suspend_Process(MK_HANDLE_t _hProcess){
    int ret = command(DRIVER_NUM_PM, 1, _hProcess, 0);
    return ret;
}

MK_ERROR_e _mk_Resume_Process (MK_HANDLE_t _hProcess){
    int ret = command(DRIVER_NUM_PM, 2, _hProcess, 0);
      return ret ;
}

void _mk_Yield(void) { //(MK_HANDLE_t _hProcess){
//void _mk_Yield(MK_HANDLE_t _hProcess){
    __attribute__ ((unused)) int sret = command(DRIVER_NUM_PM, 3, 0, 0);
//    yield();
}
int _testing (void) {
    return command(DRIVER_NUM_PM,4,0,0);
}

//int process_cb(subscribe_cb callback, void* callback_args) {
//  return subscribe(DRIVER_NUM_PM, 0, callback, callback_args);
//}


