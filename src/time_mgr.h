/// time_mgr
///
/// This module is a general timer module.  It provides access to set timers
/// and monitor them for expiration.

#ifndef TIME_MGR_H_
#define TIME_MGR_H_

#include <stdint.h>
#include <stdbool.h>

/// Structure to store timer data
typedef struct
{
    bool b_overflow;
    uint32_t end_ticks;
} time_mgr_timer_t;


void time_mgr_init(uint32_t tick_rate);
void time_mgr_tick(void);
uint32_t time_mgr_get_ticks_elapsed(void);
void time_mgr_set_timer(time_mgr_timer_t * const p_timer,
                        uint32_t timer_ticks);
bool time_mgr_get_timer_expired(time_mgr_timer_t const * const p_timer);

#endif /* TIME_MGR_H_ */
