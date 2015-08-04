#ifndef _ONEWIRE_INCLUDED_
#define _ONEWIRE_INCLUDED_

#define OW_RESET_WIDTH      500
#define OW_PRESENCE_DELAY   70
#define OW_WRITE_ZERO_WIDTH 90
#define OW_WRITE_ONE_LOW    10
#define OW_WRITE_ONE_HI     50
#define OW_READ_WIDTH       5
#define OW_READ_PADDING     60
#define OW_RECOVERY         5


#define OW_SKIP_ROM         0xcc

#define DS18B20_CONVERT     0x44
#define DS18B20_READ_SPAD   0xbe

int ow_detect_presence();

int ds18b20_get_temp(char *tmp);

#endif
