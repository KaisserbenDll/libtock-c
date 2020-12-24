#include "libvpp/vpp.h"
#include <tock.h>
#include <stdlib.h>

// Again this is declared as extern buf[128], so both app1 and app2 
// can access it.
char buf[128];
int main(void) {
  // Since printfs are broken, i am comapring the buf with a string with
  // the same message. If they are the same, i will see the syscall with
  // the signal 0x11111111 sent.
  

  char str[128]="No";
  memcpy(str,buf,128);

  printf("Address buffer App1 %p\n", buf);
  printf("Content buffer  App1%s\n", buf);
  int result = strcmp(buf, str);
  /*if (result== 0) {
  __attribute__((unused)) MK_ERROR_e error= _mk_Send_Signal(0x8001,0x11111111);

  } else {
  __attribute__((unused)) MK_ERROR_e error2= _mk_Send_Signal(0x8001,0x00000000);
  }*/

}
