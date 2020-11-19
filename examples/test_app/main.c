 #include <timer.h>
#include "libvpp/vpp.h"
#include <tock.h>
#include "internal/alarm.h"
volatile int i = 0;

//char* share[MK_IPC_MGT_LENGTH];
//void* share;
 char buf[128];
int main(void) {
    /*share = Share(0x4001);
    char str[] = "Hello";
    int result = strcmp((char*) share, str);
    if (result == 0) {
  __attribute__((unused)) MK_ERROR_e error= _mk_Send_Signal(0x8001,0x11111111);

  } else {
  __attribute__((unused)) MK_ERROR_e error2= _mk_Send_Signal(0x8001,0x00000000);
  }*/

__attribute__ ((unused)) int ret =register_share(buf);



//    void cb(__attribute__ ((unused)) int unused0, __attribute__ ((unused)) int unused1,
//          __attribute__ ((unused)) int unused2, __attribute__ ((unused)) void* unused4) {
    __attribute__((unused)) MK_HANDLE_t handle = _mk_Get_Mailbox_Handle(0x8001) ;
    __attribute__((unused)) MK_ERROR_e error = _mk_Send_Signal(0x8001,0x88888888);
  __attribute__((unused)) MK_ERROR_e error1 = _mk_Get_Error(0x8001);

    return 0;
}
