// #include "mailbox.h"
#include <timer.h>
#include "libvpp/vpp.h"
#include <tock.h>
// #include "internal/alarm.h"
volatile int i = 0;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <console.h>

char buf[128];
//char* share = 'A';

//void* share;

int main(void) {
  char str[128];
  memcpy(str,buf,128);
  int result = strcmp(buf, str);
  if (result== 0) {
  __attribute__((unused)) MK_ERROR_e error= _mk_Send_Signal(0x8001,0x11111111);

  } else {
  __attribute__((unused)) MK_ERROR_e error2= _mk_Send_Signal(0x8001,0x00000000);
  }
/*
  char str[]="Sharing";
  //printf("%s",str);
  //  share = "Hello";
*/
}
