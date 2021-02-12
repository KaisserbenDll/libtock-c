#include "libvpp/vpp.h"


// Initial Values of FIFOs 
#define m_MTU_OUT_init      8 
#define m_Size_OUT_init     4
#define m_Read_IN_init      0
#define m_Write_OUT_init    0

#define m_MTU_IN_init      8 
#define m_Size_IN_init     4
#define m_Read_OUT_init     0
#define m_Write_IN_init    0

// Parameters Data Struct
 struct parameters_struct {
    uint16_t m_MTU_OUT; // FIFO OUT size of data chunk
    uint16_t m_Size_OUT; // FIFO OUT max number of data chunks
    uint32_t m_Read_IN; // Index of last data chunk read from FIFO IN
    uint32_t m_Write_OUT; // Index of next chunk to be written in FIFO OUT
    void* m_Buff_OUT; // Array of data chunks. The actual FIFO OUT
 };

// Return Data Struct
 struct return_struct {
    uint16_t m_MTU_IN; 
    uint16_t m_Size_In;
    uint32_t m_Read_OUT;
    uint32_t m_Write_IN;
    void* m_Buff_IN;
 };



