#include "libvpp/vpp.h"
#include <tock.h>
// This the definition of the buffer that is registered to be shared 
// with the AppId 1. This buffer has been declared in the `vpp.h` as 
// extern char buf[128], otherwise the second application can never 
// access it.
char buf[128]="Sharing";
int main(void) {
  // The register_share simply allows access for the AppId 1 to have
  // access over buf using the allow syscall.
__attribute__ ((unused)) int ret =register_share(buf);
    return 0;
}
