#include "stm32f103x6.h"

static void enableSysTick(void);

volatile uint32_t ticks = 0;

int main(void)
{
	enableSysTick();
	RCC->APB1ENR |= RCC_APB1ENR_USBEN;
}

static void enableSysTick(void)
{
	SysTick->LOAD = (uint32_t)((72000000UL/1000)-1);
	NVIC_SetPriority(SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL);
	SysTick->VAL = 0UL;
	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
	NVIC_EnableIRQ(SysTick_IRQn);
}

void SysTick_Handler(void)
{
	ticks++;
}
