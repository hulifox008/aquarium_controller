#ifndef _STM32F1X_INCLUDED_
#define _STM32F1X_INCLUDED_


#define TIM2_BASE       0x40000000

#define TIM3_BASE       0x40000400

#define TIM4_BASE       0x40000800

#define TIM5_BASE       0x40000c00

#define TIM6_BASE       0x40001000
#define TIM6_CR1        (TIM6_BASE)
#define BASIC_TIM_CR1_CEN    (1<<0)
#define BASIC_TIM_CR1_UDIS   (1<<1)
#define BASIC_TIM_CR1_URS    (1<<2)
#define BASIC_TIM_CR1_OPM    (1<<3)
#define BASIC_TIM_CR1_ARPE   (1<<7)

#define TIM6_CR2        (TIM6_BASE+4)

#define TIM6_DIER       (TIM6_BASE+0xc)
#define BASIC_TIM_DIER_UIE   (1<<0)
#define BASIC_TIM_DIER_UDE   (1<<8)

#define TIM6_SR         (TIM6_BASE+0x10)
#define BASIC_TIM_SR_UIF     (1<<0)

#define TIM6_EGR        (TIM6_BASE+0x14)
#define TIM6_CNT        (TIM6_BASE+0x24)
#define TIM6_PSC        (TIM6_BASE+0x28)
#define TIM6_ARR        (TIM6_BASE+0x2C)

#define GPIOA_BASE          0x40010800
#define GPIOB_BASE          0x40010c00
#define GPIOC_BASE          0x40011000
#define GPIOD_BASE          0x40011400
#define GPIOE_BASE          0x40011800
#define GPIOF_BASE          0x40011c00
#define GPIOG_BASE          0x40012000
    
#define GPIO_CRL_OFFSET     0
#define GPIO_MODE_INPUT     0
#define GPIO_MODE_10M       1   
#define GPIO_MODE_2M        2
#define GPIO_MODE_50M       3
#define GPIO_CNF_ANALOG     0
#define GPIO_CNF_IN_HIZ     1
#define GPIO_CNF_IN_PULL    2
#define GPIO_CNF_OUT_PP     0 /* Output Push-Pull */
#define GPIO_CNF_OUT_OD     1 /* output Open-Drain */
#define GPIO_CNF_ALT_PP     2
#define GPIO_CNF_ALT_OD     3


#define GPIO_CRH_OFFSET     0x04
#define GPIO_IDR_OFFSET     0x08
#define GPIO_ODR_OFFSET     0x0c
#define GPIO_BSRR_OFFSET    0x10
#define GPIO_BRR_OFFSET     0x14
#define GPIO_LCKR           0x18






/* RCC Registers
 */
#define RCC_BASE        0x40021000

#define RCC_CR          (RCC_BASE)
#define RCC_CR_PLL_RDY  (1<<25)
#define RCC_CR_PLL_ON   (1<<24)
#define RCC_CR_HSE_RDY  (1<<17)
#define RCC_CR_HSE_ON   (1<<16)

#define RCC_CFGR        (RCC_BASE+4)
#define RCC_CIR         (RCC_BASE+8)

#define RCC_APB2ENR     (RCC_BASE+0x18)
#define RCC_APB2ENR_IOPA_EN (1<<2)
#define RCC_APB1ENR     (RCC_BASE+0x1c)
#define RCC_APB1ENR_TIM2_EN (1<<0)
#define RCC_APB1ENR_TIM3_EN (1<<1)
#define RCC_APB1ENR_TIM4_EN (1<<2)
#define RCC_APB1ENR_TIM5_EN (1<<3)
#define RCC_APB1ENR_TIM6_EN (1<<4)
#define RCC_APB1ENR_BKP_EN  (1<<27)
#define RCC_APB1ENR_PWR_EN  (1<<28)

#define RCC_BDCR        (RCC_BASE+0x20)
#define RCC_BDCR_LSE_ON (1<<0)
#define RCC_BDCR_LSE_RDY (1<<1)
#define RCC_BDCR_RTC_EN (1<<15)

#define PWR_BASE        0x40007000

#define PWR_CR          (PWR_BASE)
#define PWR_CR_DBP      (1<<8)

#endif
