/* Resource allocation:
 * PA0, Timer2 CH1:  PWM for airpump.
 * Timer3:  PWM for light control 2.
 * Timer6:  Time measurement for udelay() function.
 *
 * : 1-Wire temperature (DS18B20)
 */

#include "types.h"
#include "io.h"
#include "stm32f1x.h"

char tmp = 0x5a;

void sys_init()
{
    u_int32_t   t;

    /* set flash interface wait states */
    writel(0x32, 0x40022000);

    /* Enable HSE clock */
    writel(readl(RCC_CR) | RCC_CR_HSE_ON, RCC_CR);
    while( !(readl(RCC_CR) & RCC_CR_HSE_RDY));

    /* PLLMUL = 7 (9x)
     * PLLSRC -> HSE
     */
    t = readl(RCC_CFGR);
    t = t & ~0x00C00000 | 0x001d0000;
    writel(t, RCC_CFGR);

    /* Enable PLL and wait for ready. */
    writel(readl(RCC_CR) | RCC_CR_PLL_ON, RCC_CR);
    while( !(readl(RCC_CR) & RCC_CR_PLL_RDY));

    /* Switch clock to PLL */
    t = readl(RCC_CFGR);
    t = t & 0xFFFF0000 | 0x2402;
    writel(t, RCC_CFGR);

    /* Enable clock */
    writel(readl(RCC_APB1ENR) 
        | RCC_APB1ENR_BKP_EN 
        | RCC_APB1ENR_PWR_EN
        | RCC_APB1ENR_TIM2_EN
        | RCC_APB1ENR_TIM3_EN
        | RCC_APB1ENR_TIM6_EN,
        RCC_APB1ENR);

    writel(readl(RCC_APB2ENR)
        | RCC_APB2ENR_IOPA_EN,
        RCC_APB2ENR);

    /* Enable writing to backup domain. */
    writel(readl(PWR_CR) | PWR_CR_DBP, PWR_CR);

    /* Turn on RTC */
    writel(readl(RCC_BDCR) | RCC_BDCR_LSE_ON, RCC_BDCR);
    while( !(readl(RCC_BDCR) & RCC_BDCR_LSE_RDY));
    t = readl(RCC_BDCR);
    t = t & ~0x300 | 0x8100;
    writel(t, RCC_BDCR);
}

void timer_init()
{
    u_int32_t t;

    /* Init timer 6 */
    t = readl(TIM6_CR1);
    t = t & ~(BASIC_TIM_CR1_CEN | BASIC_TIM_CR1_UDIS | BASIC_TIM_CR1_ARPE);
    t |= (BASIC_TIM_CR1_OPM | BASIC_TIM_CR1_URS);
    writel(t, TIM6_CR1);

    t = readl(TIM6_DIER);
    t &= ~(BASIC_TIM_DIER_UIE | BASIC_TIM_DIER_UDE);
    writel(t, TIM6_DIER);

    writel(0, TIM6_CNT);
    writel(0, TIM6_PSC);
}

void gpio_init()
{
    writel(GPIO_MODE_2M | GPIO_CNF_ALT_PP<<2, GPIOA_BASE+GPIO_CRL_OFFSET);
}

void init_airpump_pwm()
{
    writel(0x3b, GP_TIMER_PSC(TIM2_BASE));
    writel(0xea60, GP_TIMER_ARR(TIM2_BASE));
    writel(0x1, GP_TIMER_CCER(TIM2_BASE));
    writel(0x7530, GP_TIMER_CCR1(TIM2_BASE));
    writel(0x60, GP_TIMER_CCMR1(TIM2_BASE));
    writel(1, GP_TIMER_CR1(TIM2_BASE));
}

void udelay(unsigned int duration)
{
    #define TIM6_FREQ   72000000
    do {
        if(duration>=900) { /* Avoid ARR register overflow */
           duration-=900;
           writel(TIM6_FREQ/1000000*900, TIM6_ARR);
        }else{
           writel(TIM6_FREQ/1000000*duration, TIM6_ARR);
           duration = 0;
        }
           
        writel(0, TIM6_SR);
        writel(readl(TIM6_CR1) | BASIC_TIM_CR1_CEN, TIM6_CR1);
        while( !(readl(TIM6_SR) & BASIC_TIM_SR_UIF));
    }while(duration);
}

void ow_send_low_pulse(duration)
{
    u_int32_t t;
    t=readl(GPIOA_BASE+GPIO_CRL_OFFSET);
    t = t&~0xF | (GPIO_MODE_2M | GPIO_CNF_OUT_OD<<2);
    writel(t, GPIOA_BASE+GPIO_CRL_OFFSET);
    udelay(duration);
    t=readl(GPIOA_BASE+GPIO_CRL_OFFSET);
    t = t&~0xF | (GPIO_MODE_INPUT | GPIO_CNF_IN_HIZ<<2);
    writel(t, GPIOA_BASE+GPIO_CRL_OFFSET);
}

int ow_get_line_status()
{
    return (readl(GPIOA_BASE+GPIO_IDR_OFFSET) & 1);
}

int main()
{
    sys_init();
    timer_init();
    gpio_init();
    volatile int i;

    init_airpump_pwm();
    while(1) {
/*        ds18b20_get_temp(&tmp); */

        udelay(1000000);

    }
}
