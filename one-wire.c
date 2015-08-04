#include "types.h"
#include "bsp.h"
#include "one-wire.h"

void ow_write_one()
{
    ow_send_low_pulse(OW_WRITE_ONE_LOW);
    udelay(OW_WRITE_ONE_HI);
}

void ow_write_zero()
{
    ow_send_low_pulse(OW_WRITE_ZERO_WIDTH);
}

int ow_read_bit()
{
    int t;
    ow_send_low_pulse(OW_READ_WIDTH);
    udelay(OW_RECOVERY);
    t = ow_get_line_status();
    udelay(OW_READ_PADDING);
    return t!=0;
}


void ow_send_byte(u_int8_t v)
{
    int i;
    for(i=0;i<8;i++){
        if(v & 1)
            ow_write_one();
        else
            ow_write_zero();
        v=v>>1;
        udelay(OW_RECOVERY);
    }
}

u_int8_t ow_receive_byte()
{
    u_int8_t t = 0;
    int i;
    for(i=0;i<8;i++){
        t=t>>1;
        if(ow_read_bit())
            t |= 0x80;
    }
    return t;
}

int ow_detect_presence()
{
    ow_send_low_pulse(OW_RESET_WIDTH);
    udelay(OW_PRESENCE_DELAY);

    udelay(100);
    return (ow_get_line_status() == 0);
}


/* tmp is in 0.5 C */
int ds18b20_get_temp(char *tmp)
{
/*
    if(!ow_detect_presence())    
        return -1;
*/
    ow_detect_presence();

    *tmp = 0;
    ow_send_byte(OW_SKIP_ROM);
    ow_send_byte(DS18B20_READ_SPAD);
    *tmp = ow_receive_byte()>>3;
    *tmp |= ow_receive_byte() << 5;


    ow_detect_presence();
    ow_send_byte(OW_SKIP_ROM);
    ow_send_byte(DS18B20_CONVERT);
    return 0;
}


