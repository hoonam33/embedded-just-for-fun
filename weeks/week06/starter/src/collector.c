#include "mission.h"
#include "platform.h"
#include <stddef.h>

bool collector_step(SampleReport *out)
{
    if (out == NULL) { return false; }
    EventBatch batch;
    if (!event_take(&batch)) { return false; }
    bool previous = platform_irq_save_disable();
    SampleReport report = {0};
    report.request_tick = platform_timer_now();
    report.requests = batch.pending;
    report.coalesced = batch.pending;
    report.dropped = 0u;
    report.value = platform_sensor_read();
    platform_publish(&report);
    platform_irq_restore(previous);
    *out = report;
    return true;
}
