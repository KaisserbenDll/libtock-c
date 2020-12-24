#pragma once

#include "tock.h"

#define DRIVER_NUM_NONVOLATILE_STORAGE 0x50001

#ifdef __cplusplus
extern "C" {
#endif

int nonvolatile_storage_internal_read_done_subscribe(subscribe_cb cb, void *userdata);
int nonvolatile_storage_internal_write_done_subscribe(subscribe_cb cb, void *userdata);

int nonvolatile_storage_internal_read_buffer(uint8_t* buffer, uint32_t len);
int nonvolatile_storage_internal_write_buffer(uint8_t* buffer, uint32_t len);

int nonvolatile_storage_internal_get_number_bytes(void);
int nonvolatile_storage_internal_read(uint32_t offset, uint32_t length);
int nonvolatile_storage_internal_write(uint32_t offset, uint32_t length);

int write_nvm(uint8_t *writebuf, 
              size_t size,
              size_t offset,
              size_t len);
int read_nvm(uint8_t *readbuf, size_t size, size_t offset, size_t len);

#ifdef __cplusplus
}
#endif
