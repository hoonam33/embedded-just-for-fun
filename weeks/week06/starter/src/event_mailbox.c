#include "mission.h"
#include "platform.h"
#include <stddef.h>

EventMailbox g_events = {0u, 0u, 0u};

void event_reset(void)
{
    g_events.pending = 0u;
    g_events.dropped = 0u;
    g_events.last_tick = 0u;
}

void event_post_isr(uint32_t tick)
{
    g_events.pending = 1u;
    g_events.last_tick = tick;
}

bool event_take(EventBatch *out)
{
    if (out == NULL) { return false; }
    (void)platform_irq_save_disable();
    out->pending = g_events.pending;
    out->dropped = g_events.dropped;
    out->last_tick = g_events.last_tick;
    platform_interleave(); /* 이 Hook의 위치와 호출 횟수는 유지한다. */
    platform_irq_restore(true);
    if (out->pending == 0u) { return false; }
    g_events.pending = 0u;
    g_events.dropped = 0u;
    g_events.last_tick = 0u;
    return true;
}
