#include "stm32f103x6.h"

extern long __bss_start__;
extern long __bss_end__;
extern long __stack;
extern long __data_start__;
extern long __data_end__;
extern long __etext;

#define SECT_VECTABLE 	__attribute__((section(".isr_vector"), __used__))
#define WEAK 			__attribute__((weak))
#define NAKED 			__attribute__((naked))

extern int main(void);

uint32_t SystemCoreClock;

WEAK void SystemInit(void)
{
}

WEAK void SystemCoreClockUpdate(void)
{
}

static void ram_init(void)
{
	for(long* dest = __bss_start__; dest < __bss_end__; dest++)
	{
		*dest = 0;
	}

	long* src = __etext;
	for(long* dest = __data_start__; dest < __data_end__; dest++)
	{
		*dest = *src++;
	}
}

NAKED void Reset_Handler(void)
{
	asm("bl ram_init" 	:: "i" (ram_init));
	asm("bl SystemInit" :: "i" (SystemInit));
	asm("bl main"		:: "i" (main));
	while(1);
}

WEAK void Default_Handler(void)
{
	while(1);
}

#define DEFAULT __attribute__((weak, alias("Default_Handler")))


