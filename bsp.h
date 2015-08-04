#ifndef _BSP_INCLUDED_
#define _BSP_INCLUDED_

/* Send a low pulse on data line. "duration" is in microsecond.*/
void ow_send_low_pulse(unsigned int duration);

/* Get current status of data line. */
int  ow_get_line_status();

void udelay(unsigned int duration);

#endif
