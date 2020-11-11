#include "processmanager.h"
//#include <stdio.h>

volatile int i = 0;

int main(void) {
        MK_HANDLE_t _hProcess= 1 ;
        //MK_ERROR_e return_value = _mk_Suspend_Process(_hProcess);
//        _mk_Yield();
     MK_ERROR_e return_value = _mk_Resume_Process(_hProcess);
     // _testing();
       /// _mk_Resume_Process(_hProcess);
       if (return_value == 5 ){
          while(1) {i++; }   
       } 
       

//       _mk_Yield(_hProcess);
//         _testing();
//   void *ptr;
//   printf("The size of pointer value : %d", sizeof(ptr));
//  printf("Jump GPIO pin 0 high to test.\n");
     return 0;
}
