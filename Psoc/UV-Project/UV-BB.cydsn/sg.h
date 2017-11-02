#ifndef __SG_H
#define __SG_H

#include <project.h>
    
float sg_measure(void);
float sg_get_strain(void);
unsigned int uv_get_pd_string(char*);
void sg_uart();

#endif // __SG_H
