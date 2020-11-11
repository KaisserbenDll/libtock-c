#include "mailbox.h"
#include "tock.h"

MK_HANDLE_t _mk_Get_Mailbox_Handle(MK_MAILBOX_ID_u _eMailboxID){
    int ret = command(VPP_DRIVER_NUM, 5, _eMailboxID, 0);
    return ret;
}
MK_ERROR_e _mk_Send_Signal(MK_HANDLE_t _hMailbox, MK_BITMAP_t _eSignal){
    return command(VPP_DRIVER_NUM,6,_hMailbox,_eSignal);
}
MK_BITMAP_t _mk_Get_Signal(MK_HANDLE_t _hMailbox){
    return command(VPP_DRIVER_NUM,7,_hMailbox,0);
}
