#ifndef _IO_INCLUDED_
#define _IO_INCLUDED_

#define writeb(v, a)    (*(volatile unsigned char *)(a) = (v))
#define writew(v, a)    (*(volatile unsigned short *)(a) = (v))
#define writel(v, a)    (*(volatile unsigned int *)(a) = (v))
#define readb(a)        (*(volatile unsigned char*)(a))
#define readw(a)        (*(volatile unsigned short*)(a))
#define readl(a)        (*(volatile unsigned int*)(a))


#endif
