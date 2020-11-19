/* vim: set sw=2 expandtab tw=80: */

#include <stdio.h>

#include <console.h>
#include <timer.h>

int main(void) {
  const char *a = "h";
  while (1) {
    printf(a);
    //delay_ms(10000);
  }
}
