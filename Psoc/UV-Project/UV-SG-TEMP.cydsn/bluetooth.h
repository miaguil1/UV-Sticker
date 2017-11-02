#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <project.h>   

typedef enum { blpm_active = 0x01, blpm_sleep, blpm_deepsleep } blpm_t; 
typedef enum { bless_active = 0x01, bless_event_close, bless_sleep, bless_eco_on, bless_eco_stable, bless_deepsleep, bless_hibernate } bless_t;  

typedef struct {
	void (*start) (void);
    void (*process) (void);
	void (*stop) (void);
    void (*send) (char *format, ...);
    int (*is_connected) (void);
    int (*is_advertising) (void);
    int (*is_initializing) (void);
    int (*bless_in_deepsleep) (void);
    int (*bless_in_eco_on) (void);
    int (*bless_in_event_close) (void);
    blpm_t (*enter_deepsleep) (void);
    CYBLE_CONN_HANDLE_T (*get_connection_handle) (void);
    int (*indications_enabled) (void);
} const bluetooth_t;

extern bluetooth_t * const bluetooth;

#endif // __BLUETOOTH_H

