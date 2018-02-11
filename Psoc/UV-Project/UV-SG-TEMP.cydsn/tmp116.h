#ifndef __TMP116_H
#define __TMP116_H
#include "system.h"
    
float tmp116_get_celsius(void);
uint16 tmp116_get_uint16(void);
void tmp116_get_uint8(uint8 *tmp116_uint8);
void tmp116_string_celsius(char*);
void tmp116_uart(void);
void update_tmp116(void);

#endif // __TMP116_H
