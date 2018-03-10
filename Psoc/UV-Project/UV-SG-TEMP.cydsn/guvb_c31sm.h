#ifndef __GUVB_C31SM_H
#define __GUVB_C31SM_H

#include "system.h"

const uint32 guvb_c31sm_address;
    
void setup_guvb_c31sm(void);
void soft_reset_guvb_c31sm(void);
void shutdown_guvb_c31sm(void);
void wakeup_guvb_c31sm(void);
uint8 guvb_c31sm_chipid(void);
uint8 guvb_c31sm_read_register(uint32);
uint16 guvb_c31sm_get_uint16(void);
float guvb_c31sm_get_uv(void);
float guvb_c31sm_get_pd(void);
float guvb_c31sm_get_index(void);
void guvb_c31sm_get_pd_string(char *uv_pd_string);
void guvb_c31sm_get_uint8(uint8 *uv_uint8);
void guvb_c31sm_uart(void);
void guvb_c31sm_update_UV();

#endif // __UV_H

