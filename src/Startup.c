#include "stm32f103x6.h"

extern long __bss_start__[];
extern long __bss_end__[];
extern long __stack[];
extern long __data_start__[];
extern long __data_end__[];
extern long __etext[];

#define SECT_VECTABLE 	__attribute__((section(".isr_vector"), __used__))
#define WEAK 			__attribute__((weak))
#define NAKED 			__attribute__((naked))

extern int main(void);

uint32_t SystemCoreClock;

WEAK void SystemInit(void)
{
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));

	RCC->CFGR |= (RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9 | RCC_CFGR_ADCPRE_1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_USBPRE);
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	RCC->CFGR |= (RCC_CFGR_SW_PLL);
	while(!(RCC->CFGR & RCC_CFGR_SWS));	//Clock will be running max speed at this point

	SystemCoreClock = 72000000UL;
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

DEFAULT void NMI_Handler(void);
DEFAULT void HardFault_Handler(void);
DEFAULT void MemManage_Handler(void);
DEFAULT void BusFault_Handler(void);
DEFAULT void UsageFault_Handler(void);
DEFAULT void SVC_Handler(void);
DEFAULT void DBG_Mon_Handler(void);
DEFAULT void PendSV_Handler(void);
DEFAULT void SysTick_Handler(void);
DEFAULT void WWDG_Handler(void);
DEFAULT void PVD_Handler(void);
DEFAULT void Tamper_Handler(void);
DEFAULT void RTC_Handler(void);
DEFAULT void Flash_Handler(void);
DEFAULT void RCC_Handler(void);
DEFAULT void EXTI0_Handler(void);
DEFAULT void EXTI1_Handler(void);
DEFAULT void EXTI2_Handler(void);
DEFAULT void EXTI3_Handler(void);
DEFAULT void EXTI4_Handler(void);
DEFAULT void DMA1_Channel1_Handler(void);
DEFAULT void DMA1_Channel2_Handler(void);
DEFAULT void DMA1_Channel3_Handler(void);
DEFAULT void DMA1_Channel4_Handler(void);
DEFAULT void DMA1_Channel5_Handler(void);
DEFAULT void DMA1_Channel6_Handler(void);
DEFAULT void DMA1_Channel7_Handler(void);
DEFAULT void ADC1_2_Handler(void);
DEFAULT void USB_HP_CAN_TX_Handler(void);
DEFAULT void USB_LP_CAN_RX0_Handler(void);
DEFAULT void CAN1_RX1_Handler(void);
DEFAULT void CAN1_SCE_Handler(void);
DEFAULT void EXTI9_5_Handler(void);
DEFAULT void TIM1_BRK_Handler(void);
DEFAULT void TIM1_UP_Handler(void);
DEFAULT void TIM1_TRG_Handler(void);
DEFAULT void TIM1_CC_Handler(void);
DEFAULT void TIM2_Handler(void);
DEFAULT void TIM3_Handler(void);
DEFAULT void TIM4_Handler(void);
DEFAULT void I2C1_EV_Handler(void);
DEFAULT void I2C1_ER_Handler(void);
DEFAULT void I2C2_EV_Handler(void);
DEFAULT void I2C2_ER_Handler(void);
DEFAULT void SPI1_Handler(void);
DEFAULT void SPI2_Handler(void);
DEFAULT void USART1_Handler(void);
DEFAULT void USART2_Handler(void);
DEFAULT void USART3_Handler(void);
DEFAULT void EXTI15_10_Handler(void);
DEFAULT void RTC_Alarm_Handler(void);
DEFAULT void USB_WKUP_Handler(void);
DEFAULT void TIM8_BRK_Handler(void);
DEFAULT void TIM8_UP_Handler(void);
DEFAULT void TIM8_TRG_Handler(void);
DEFAULT void TIM8_CC_Handler(void);
DEFAULT void ADC_3_Handler(void);
DEFAULT void FSMC_Handler(void);
DEFAULT void SDIO_Handler(void);
DEFAULT void TIM5_Handler(void);
DEFAULT void SPI3_Handler(void);
DEFAULT void UART4_Handler(void);
DEFAULT void UART5_Handler(void);
DEFAULT void TIM6_Handler(void);
DEFAULT void TIM7_Handler(void);
DEFAULT void DMA2_Channel1_Handler(void);
DEFAULT void DMA2_Channel2_Handler(void);
DEFAULT void DMA2_Channel3_Handler(void);
DEFAULT void DMA2_Channel4_5_Handler(void);

typedef struct {
	long* initial_stack;
	void(*vectors[])(void);
} vector_table_t;

SECT_VECTABLE const vector_table_t __vector_table = {
	.initial_stack = __stack,
	.vectors = {
		Reset_Handler,
		NMI_Handler,
		HardFault_Handler,
		MemManage_Handler,
		BusFault_Handler,
		UsageFault_Handler,
		0,
		SVC_Handler,
		DBG_Mon_Handler,
		0,
		PendSV_Handler,
		SysTick_Handler,
		WWDG_Handler,
		PVD_Handler,
		Tamper_Handler,
		RTC_Handler,
		Flash_Handler,
		RCC_Handler,
		EXTI0_Handler,
		EXTI1_Handler,
		EXTI2_Handler,
		EXTI3_Handler,
		EXTI4_Handler,
		DMA1_Channel1_Handler,
		DMA1_Channel2_Handler,
		DMA1_Channel3_Handler,
		DMA1_Channel4_Handler,
		DMA1_Channel5_Handler,
		DMA1_Channel6_Handler,
		DMA1_Channel7_Handler,
		ADC1_2_Handler,
		USB_HP_CAN_TX_Handler,
		USB_LP_CAN_RX0_Handler,
		CAN1_RX1_Handler,
		CAN1_SCE_Handler,
		EXTI9_5_Handler,
		TIM1_BRK_Handler,
		TIM1_UP_Handler,
		TIM1_TRG_Handler,
		TIM1_CC_Handler,
		TIM2_Handler,
		TIM3_Handler,
		TIM4_Handler,
		I2C1_EV_Handler,
		I2C1_ER_Handler,
		I2C2_EV_Handler,
		I2C2_ER_Handler,
		SPI1_Handler,
		SPI2_Handler,
		USART1_Handler,
		USART2_Handler,
		USART3_Handler,
		EXTI15_10_Handler,
		RTC_Alarm_Handler,
		USB_WKUP_Handler,
		TIM8_BRK_Handler,
		TIM8_UP_Handler,
		TIM8_TRG_Handler,
		TIM8_CC_Handler,
		ADC_3_Handler,
		FSMC_Handler,
		SDIO_Handler,
		TIM5_Handler,
		SPI3_Handler,
		UART4_Handler,
		UART5_Handler,
		TIM6_Handler,
		TIM7_Handler,
		DMA2_Channel1_Handler,
		DMA2_Channel2_Handler,
		DMA2_Channel3_Handler,
		DMA2_Channel4_5_Handler
	}
};
