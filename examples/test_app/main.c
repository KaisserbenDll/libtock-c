 #include <timer.h>
#include "libvpp/vpp.h"
#include <tock.h>
#include "internal/alarm.h"
volatile int i = 0;

int main(void) {
//    void cb(__attribute__ ((unused)) int unused0, __attribute__ ((unused)) int unused1,
//          __attribute__ ((unused)) int unused2, __attribute__ ((unused)) void* unused4) {
//    __attribute__((unused)) MK_HANDLE_t handle = _mk_Get_Mailbox_Handle(0x8001) ;
//     __attribute__((unused)) MK_ERROR_e error = _mk_Send_Signal(0x8001,0x88888888);
//  __attribute__((unused)) MK_ERROR_e error1 = _mk_Get_Error(0x8001);
//   __attribute__((unused)) MK_TIME_t timenow = _mk_Get_Time();
//   __attribute__((unused)) int waited = alarm_internal_set(500);
//                   while (1)
//                   {
//                        //__attribute__((unused)) MK_TIME_t timenow = _mk_Get_Time();
//                      i++;
//                   };
                  
//                } ;
        

      *buf = "Hello There";
      *buf  = register_share();

   /*delay_ms(2500);
  while (1)
   {      i++ ;  };*/
         //delay_ms(500);
  /*while (1)
   {      i++ ;  };*/
      // __attribute__((unused)) MK_HANDLE_t handle = _mk_Get_Mailbox_Handle(0x8001) ;

  //__attribute__((unused)) int ret = some_subscribe_test(0x8001,cb,NULL);

       /*void cb(__attribute__ ((unused)) int unused0,
                __attribute__ ((unused)) int unused1,
                __attribute__ ((unused)) int unused2,
               __attribute__ ((unused)) void* unused3) {
                while (1){i++;}
               } ;
        */

/*
       MK_HANDLE_t handle = _mk_Get_Process_Handle(0x8001) ;
      //  __attribute__((unused)) MK_ERROR_e error = _mk_Get_Error(handle);
       __attribute__((unused)) int ret =  Share_Slice (handle) ;*/
      //shared_buff[6] = "Hello" ;
    //    _mk_Get_Access_IPC(handle);
    
/* MK_HANDLE_t mgt_mailbox = _mk_Get_Mailbox_Handle(0x8001);

    //__attribute__((unused)) MK_ERROR_e error = _mk_Send_Signal(mgt_mailbox,0x88888888);
    //__attribute__((unused)) MK_ERROR_e error1 = _mk_Send_Signal(mgt_mailbox,0x44444444);
    //__attribute__((unused)) MK_ERROR_e error2 = _mk_Send_Signal(mgt_mailbox,0x22222222);
    __attribute__((unused)) MK_ERROR_e error3 = _mk_Send_Signal(mgt_mailbox,0x00100101);
    __attribute__((unused)) MK_ERROR_e error4 = _mk_Send_Signal(mgt_mailbox,0x10001010);

    __attribute__((unused)) MK_BITMAP_t retrieve_sig = _mk_Get_Signal(mgt_mailbox);
    __attribute__((unused)) MK_BITMAP_t retrieve_sig1 = _mk_Get_Signal(mgt_mailbox);
    __attribute__((unused)) MK_ERROR_e error5 = _mk_Send_Signal(mgt_mailbox,0x00001111);
    __attribute__((unused)) MK_BITMAP_t retrieve_sig2 = _mk_Get_Signal(mgt_mailbox);
    __attribute__((unused)) MK_BITMAP_t retrieve_sig3 = _mk_Get_Signal(mgt_mailbox);*/

    //__attribute__((unused)) MK_BITMAP_t retrieve_sig2 = _mk_Get_Signal(mgt_mailbox);
    //__attribute__((unused)) MK_BITMAP_t retrieve_sig3 = _mk_Get_Signal(mgt_mailbox);
     
/*
    for (int j=0 ; j<5 ; j++){
     alarm_internal_subscribe(cb,NULL);
    }*/
     /*while (1) {
    delay_ms(250);
    }*/
}
