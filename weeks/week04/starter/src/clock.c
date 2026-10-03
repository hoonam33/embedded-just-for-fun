#include "mission.h"
#include "stm32f0xx_hal.h"

bool board_clock_init(void)
{
    /* TODO C1: HSI 8 MHz / 2 * 12, SYSCLK/HCLK/PCLK1 48 MHz.
       RCC_OscInitTypeDef, RCC_ClkInitTypeDef를 초기화한 뒤 HAL에 전달하세요.
       HSI ON + 기본 Calibration, PLL ON, PREDIV DIV1을 명시하세요.
       OscConfig -> ClockConfig(FLASH_LATENCY_1). 실패 즉시 false. */
    return false;
}
