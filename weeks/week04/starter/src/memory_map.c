#include "mission.h"

MemoryRegion memory_region(uint32_t address)
{
    /* TODO M1: Datasheet 근거로 Flash/SRAM/GPIOA/RCC 경계를 반영하세요.
       단일 주소 숫자만 분류합니다. Pointer 변환이나 역참조는 금지합니다. */
    (void)address;
    return MEMORY_UNKNOWN;
}
