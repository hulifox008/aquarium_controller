/* #define  TEST_LIGHT */

#ifdef TEST_LIGHT
#include <stdio.h>
#include <sys/types.h>
#else
#include "types.h" 
#endif

struct light_control_point {
    u_int8_t  hour;
    u_int8_t  intense;
};

struct light_control_point light_profile[] = {
    {6,  0},
    {8,  80},
    {19, 80},
    {23, 0},
};

u_int8_t get_light_intense(u_int32_t seconds)
{
    int h = seconds/3600;
    int i;
    int profile_len = sizeof(light_profile)/ sizeof(light_profile[0]);
    
    for(i=0;i<profile_len;i++) {
        u_int8_t h1 = light_profile[i].hour;
        u_int8_t h2 = light_profile[(i+1)%profile_len].hour;
        int duration =  (h2 + 24 - h1)%24;
        if(h>=h1 && h<h1+duration) {
            u_int8_t intense1 = light_profile[i].intense;
            u_int8_t intense2 = light_profile[(i+1)%profile_len].intense;
            int delta = (intense2-intense1)*(int)(seconds-h1*3600)/(duration*3600);
            return intense1 + delta;
        }
    }
    return 0;
}

#ifdef TEST_LIGHT  
int main()
{
    u_int32_t i;
    for(i=0;i<24*3600;i+=600)
        printf("%02d:%02d %2d\n", i/3600, (i%3600)/60, get_light_intense(i));
    return 0;
}

#endif
