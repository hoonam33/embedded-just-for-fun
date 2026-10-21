#include "mission.h"
#include "platform.h"

void timer_isr(void)
{
    uint32_t tick = platform_timer_now();
    SampleReport report = {tick, 1u, 0u, 0u, 0u};
    report.value = platform_sensor_read();
    platform_publish(&report);
    platform_delay_ms(10u);
    event_post_isr(tick);
    platform_timer_service();
}
