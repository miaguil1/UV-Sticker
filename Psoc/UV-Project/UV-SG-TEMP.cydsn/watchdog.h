#ifndef __WATCHDOG_H
#define __WATCHDOG_H

#include <project.h>

typedef struct {
    void (*init) (void);
    void (*start) (void);
    void (*stop) (void);
    int (*is_up) (void);
} const watchdog_t;

extern watchdog_t * const watchdog;

#endif // __WATCHDOG_H

