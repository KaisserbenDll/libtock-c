// #include "mailbox.h"
// #include <timer.h>
#include "libvpp/vpp.h"
#include <tock.h>
// #include "internal/alarm.h"
// volatile int i = 0;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <console.h>
static void nop(
  int a __attribute__((unused)),
  int b __attribute__((unused)),
  int c __attribute__((unused)),
  void* d __attribute__((unused))) {}
char hello_test[] __attribute__((section(".data")))= "Hello";

int main(void) {

       /*void cb(__attribute__ ((unused)) int unused0,
                __attribute__ ((unused)) int unused1,
                __attribute__ ((unused)) int unused2,
               __attribute__ ((unused)) void* unused3) {
                while (1){i++;}
               } ;
        */
  putnstr_async(hello_test, strlen(hello_test), nop, NULL);
   __attribute__((unused)) MK_HANDLE_t handle =   _mk_Get_Process_Handle(0x8001);


    // MK_HANDLE_t handle =   _mk_Get_Access_IPC(handle);
 /*MK_HANDLE_t mgt_mailbox = _mk_Get_Mailbox_Handle(0x8001);

    //__attribute__((unused)) MK_ERROR_e error = _mk_Send_Signal(mgt_mailbox,0x88888888);
    //__attribute__((unused)) MK_ERROR_e error1 = _mk_Send_Signal(mgt_mailbox,0x44444444);
    //__attribute__((unused)) MK_ERROR_e error2 = _mk_Send_Signal(mgt_mailbox,0x22222222);
    __attribute__((unused)) MK_ERROR_e error3 = _mk_Send_Signal(mgt_mailbox,0x01110101);
    __attribute__((unused)) MK_ERROR_e error4 = _mk_Send_Signal(mgt_mailbox,0x10001010);

    __attribute__((unused)) MK_BITMAP_t retrieve_sig = _mk_Get_Signal(mgt_mailbox);
    __attribute__((unused)) MK_BITMAP_t retrieve_sig1 = _mk_Get_Signal(mgt_mailbox);
    //__attribute__((unused)) MK_BITMAP_t retrieve_sig2 = _mk_Get_Signal(mgt_mailbox);
    //__attribute__((unused)) MK_BITMAP_t retrieve_sig3 = _mk_Get_Signal(mgt_mailbox);
     */
/*
    for (int j=0 ; j<5 ; j++){
     alarm_internal_subscribe(cb,NULL);
    }*/
     /*while (1) {
    delay_ms(250);
    }*/
    return 0;
}
