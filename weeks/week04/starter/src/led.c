#include "mission.h"
#include "stm32f0xx_hal.h"

void board_led_init(void)
{
    /* TODO L1: GPIOA Clock Enable -> PA5 RESET -> Output PP/No Pull/Low Speed.
       HAL_GPIO_WritePin으로 초기 출력 LOW를 먼저 설정하세요. */
}

void board_led_toggle(void)
{
    /* TODO L2: HAL_GPIO_TogglePin으로 GPIOA의 Pin 5만 Toggle하세요. */
}
