#ifndef __TMP116_H
#define __TMP116_H
#include "common.h"
    
float tmp116_get_celsius(void);
uint16 tmp116_get_uint16(void);
unsigned int tmp116_string_celsius(char*);
void tmp116_uart(void);
#endif // __TMP116_H
