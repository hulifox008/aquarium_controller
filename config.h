#ifndef __CONFIG_INCLUDED__
#define __CONFIG_INCLUDED__

#include "types.h"

struct config_block {
    u_int8_t    airpump_on_duration;    /* in 1/10 second */
    u_int8_t    airpump_off_duration;   /* in 1/10 second */
    u_int8_t    airpump_pwm_duty;

    u_int8_t    water_temp;
};

#endif
