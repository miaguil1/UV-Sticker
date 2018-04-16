#ifndef __GUVB_C31SM_H
#define __GUVB_C31SM_H

#include "system.h"

const uint32 guvb_c31sm_address;
    
void guvb_c31sm_setup(void);
void guvb_c31sm_soft_reset(void);
void guvb_c31sm_shutdown(void);
void guvb_c31sm_wakeup(void);
uint8 guvb_c31sm_chipid(void);
void guvb_c31sm_range(void);
uint16 guvb_c31sm_nvm(void);
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

