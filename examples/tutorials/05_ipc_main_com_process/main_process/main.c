#include <ipc.h>
#include <stdio.h>
#include <string.h>
#include <timer.h>

// This main process takes advantage of the COM Process service to print something on the console

int _console_service = -1;
char _console_buf[64] __attribute__((aligned(64)));

// Variable used to tell the server that the client yields.
bool _done = false;

static void ipc_callback(__attribute__ ((unused)) int pid,
                         __attribute__ ((unused)) int len,
                         __attribute__ ((unused)) int arg2,
                         __attribute__ ((unused)) void* ud) {
  _done = true;
}

// Use the console Server to print a string
static void print_shared_buff(const char* buffer_to_print) {
  _done       = false;
  _console_buf = *buffer_to_print;
  ipc_notify_svc(_console_service);
  yield_for(&_done);
}

int main(void) {
  // Retrieve a handle to the console service.
  _console_service = ipc_discover("org.tockos.tutorials.ipc.com_process");
  if (_console_service < 0) {
    printf("No console service\n");
    return -1;
  }

  // Setup IPC for console service
  ipc_register_client_cb(_console_service, ipc_callback, NULL);
  ipc_share(_console_service, _console_buf, 64);

 // main logic
    const char* buffer_to_print= "Hello From MAIN PROCESS using COM PROCESS Service "
    print_shared_buff(*buffer_to_print);
  return 0;
}
