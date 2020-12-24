#include "libvpp/nvm.h"

int nonvolatile_storage_internal_read_done_subscribe(subscribe_cb cb, void *userdata) {
  return subscribe(DRIVER_NUM_NONVOLATILE_STORAGE, 0, cb, userdata);
}

int nonvolatile_storage_internal_write_done_subscribe(subscribe_cb cb, void *userdata) {
  return subscribe(DRIVER_NUM_NONVOLATILE_STORAGE, 1, cb, userdata);
}

int nonvolatile_storage_internal_read_buffer(uint8_t* buffer, uint32_t len) {
  return allow(DRIVER_NUM_NONVOLATILE_STORAGE, 0, (void*) buffer, len);
}

int nonvolatile_storage_internal_write_buffer(uint8_t* buffer, uint32_t len) {
  return allow(DRIVER_NUM_NONVOLATILE_STORAGE, 1, (void*) buffer, len);
}

int nonvolatile_storage_internal_get_number_bytes(void) {
  return command(DRIVER_NUM_NONVOLATILE_STORAGE, 1, 0, 0);
}

int nonvolatile_storage_internal_read(uint32_t offset, uint32_t length) {
  uint32_t arg0 = (length << 8) | 2;
  return command(DRIVER_NUM_NONVOLATILE_STORAGE, (int) arg0, (int) offset, 0);
}

int nonvolatile_storage_internal_write(uint32_t offset, uint32_t length) {
  uint32_t arg0 = (length << 8) | 3;
  return command(DRIVER_NUM_NONVOLATILE_STORAGE, (int) arg0, (int) offset, 0);
}

static bool done = false;

static void read_done(int length,
                      __attribute__ ((unused)) int arg1,
                      __attribute__ ((unused)) int arg2,
                      __attribute__ ((unused)) void* ud) {
  printf("\tFinished read! %i\n", length);
  done = true;
}

static void write_done(int length,
                       __attribute__ ((unused)) int arg1,
                       __attribute__ ((unused)) int arg2,
                       __attribute__ ((unused)) void* ud) {
  printf("\tFinished write! %i\n", length);
  done = true;
}

int write_nvm(uint8_t *writebuf, 
              size_t size,
              size_t offset,
              size_t len){
    int ret;
    // register internal write buffer
    ret = nonvolatile_storage_internal_write_buffer(writebuf, size);
     if (ret != 0) {
    printf("\tERROR setting write buffer\n");
    return ret;
     }
     //register write_done callback that will fire when the write op is done.
    ret = nonvolatile_storage_internal_write_done_subscribe(write_done, NULL);
    if (ret != 0) {
        printf("\tERROR setting write done callback\n");
        return ret;
    }
    // Perform the write operation in the Userspace RAM region 
    /*for (size_t i = 0; i < len; i++) {
    writebuf[i] = i;
    }*/
  
    // Perform the write op in the NVM region and yield. The callback registered earlier will fire
    // when the write op is done.
    done = false;
    ret  = nonvolatile_storage_internal_write(offset, len);
    if (ret != 0) {
        printf("\tERROR calling write\n");
        return ret;
    }
    yield_for(&done);

    return 0;


}

int read_nvm(uint8_t *readbuf, size_t size, size_t offset, size_t len){
  int ret;
  // Define internal read buffer, where the Flash controller should read to.
  // This is using allow syscall to register the readbuffer defined in Userspace RAM, in order
  // to copy the data into after the read op finishes. Same applies to the writebuff.
  ret = nonvolatile_storage_internal_read_buffer(readbuf, size);
  if (ret != 0) {
    printf("\tERROR setting read buffer\n");
    return ret;
  }
  // Setup callbacks
  // These callbacks will fire when the read/write are done. We are registering them 
  // at this point using subscribe syscall.
  ret = nonvolatile_storage_internal_read_done_subscribe(read_done, NULL);
  if (ret != 0) {
    printf("\tERROR setting read done callback\n");
    return ret;
  }
  done = false;
  ret  = nonvolatile_storage_internal_read(offset, len);
  if (ret != 0) {
    printf("\tERROR calling read\n");
    return ret;
  }
  yield_for(&done);

  return 0;
}
