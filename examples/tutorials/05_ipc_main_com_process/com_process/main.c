#include <ipc.h>
#include <console.h>
#include <tock.h>

// This service can control the UART console on a board.
//
// Interface
// =========
// Use the console to print the buff on the console

static void ipc_callback(int pid, int len, int buf, __attribute__ ((unused)) void* ud) {
  char* buffer_to_print = (char*) buf;
  int ret;

   if (len < 1 ) {
  return ;
  }
    // Using console to print a str.
     ret = putstr(buffer_to_print);
     if (ret != TOCK_SUCCESS ) {
     return;
     }
//    int putstr(*buffer_to_print,size_t len);

    // Signal done and service is completed, so we send a notify the client at the given process id
    ipc_notify_client(pid);
}

int main(void) {
    const char* com_process_buffer= "Hello From COM PROCESS" ;
  // Printing to console from com process without sharing the service
   putstr(com_process_buffer);
  // Register the IPC service for this app. It is identified by the PACKAGE_NAME of this app.
  ipc_register_svc(ipc_callback, NULL);
  return 0;
}
