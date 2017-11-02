#ifndef __UV_H
#define __UV_H

#include "system.h"
#include "uart.h"
    
float uv_measure(uint8);
float uv_get_pd(uint8);
void uv_get_pd_string(char*, uint8);
void uv_uart(uint8);

#endif // __UV_H
