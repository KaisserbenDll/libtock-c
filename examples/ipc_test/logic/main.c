#include <ipc.h>
#include <stdio.h>
#include <string.h>
#include <timer.h>
#include <stdlib.h>
#include <unistd.h>

#include <console.h>

int _led_service = -1;
char _led_buf[64] __attribute__((aligned(64)));

uint8_t _number_of_leds = 0;

bool _done = false;

// For this simple example, the callback only need set the yield variable.
static void ipc_callback(__attribute__ ((unused)) int pid,
                         __attribute__ ((unused)) int len,
                         __attribute__ ((unused)) int arg2,
                         __attribute__ ((unused)) void* ud) {
  //_done = true;
}

// Uses the LED service to get how many LEDs are on the board.
static uint8_t get_number_of_leds(void) {
  _done       = false;
  _led_buf[0] = 0;
  ipc_notify_svc(_led_service);
  //yield_for(&_done);

  return _led_buf[0];
}

// Set an LED with the LED service.
static void set_led(uint8_t led_index, uint8_t led_state) {
  // Turn the last LED on.
  _led_buf[0] = 1;         // Set LED state.
  _led_buf[1] = led_index; // Choose the LED.
  _led_buf[2] = led_state; // Set the LED.
  _done       = false;
  ipc_notify_svc(_led_service);
  //yield_for(&_done);
}

 //const char* ptr = "hello_world";
int main(void) {
  // Retrieve a handle to the LED service.
  /*char str1[12] = "Hello";
  char str2[12] = "World";
  char str3[13];
  int len ;
  len = strlen(str1);
  strcpy(str3,str1); 
  strcat(str1,str2);
  
  // pkg_name_buf = (char*)malloc(5);
  //int len = strlen(ptr);
  char* pkg_name_buf2 = (char*)malloc(5);

    for (int i = 0; i < 5; i++) {
    pkg_name_buf2[i] += str1[i];
  }
    __attribute__((unused)) int res =  allow(IPC_DRIVER_NUM, 0, pkg_name_buf2, len);
  */


 // _led_service = ipc_discover("aaaaaaaaaaaalogic_package");
 _led_service = ipc_discover("logic_package");
  if (_led_service < 0) {
    return -1;
  }


  // Setup IPC for LED service
  ipc_register_client_cb(_led_service, ipc_callback, NULL);
  ipc_share(_led_service, _led_buf, 64);


  // First need to get the number of LEDs.
  _number_of_leds = get_number_of_leds();
  //printf("Number of LEDs: %d\n", _number_of_leds);
  //putnstr_async(hello1, strlen(hello1), nop, NULL);
  // Then randomly turn on and off LEDs using the two services.
  /*while (1) {

    uint8_t led_index = (10 & 0xFF) % _number_of_leds;
    uint8_t led_state = (10 >> 8) > 0x7F;
    set_led(led_index, led_state);

    delay_ms(500);
  }*/

  return 0;
}
