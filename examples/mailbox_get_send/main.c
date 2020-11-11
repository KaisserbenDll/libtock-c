#include "mailbox.h"

int main(void) {


 MK_HANDLE_t mgt_mailbox = _mk_Get_Mailbox_Handle(0x8001);

    __attribute__((unused)) MK_ERROR_e error = _mk_Send_Signal(mgt_mailbox,0x88888888);
    __attribute__((unused)) MK_ERROR_e error1 = _mk_Send_Signal(mgt_mailbox,0x44444444);
    __attribute__((unused)) MK_ERROR_e error2 = _mk_Send_Signal(mgt_mailbox,0x22222222);
    //__attribute__((unused)) MK_ERROR_e error3 = _mk_Send_Signal(mgt_mailbox,0x11111111);

    __attribute__((unused)) MK_BITMAP_t retrieve_sig = _mk_Get_Signal(mgt_mailbox);
    __attribute__((unused)) MK_BITMAP_t retrieve_sig1 = _mk_Get_Signal(mgt_mailbox);
    __attribute__((unused)) MK_BITMAP_t retrieve_sig2 = _mk_Get_Signal(mgt_mailbox);
    __attribute__((unused)) MK_BITMAP_t retrieve_sig3 = _mk_Get_Signal(mgt_mailbox);

}
