/// time_mgr
///
/// This module is a general timer module.  It provides access to set timers
/// and monitor them for expiration.

#include "time_mgr.h"

#include <stddef.h>


/// Storage for the ticks elapsed
static volatile uint32_t ticks_elapsed = 0;
/// Storage for the tick rate
static volatile uint32_t tick_rate = 0;

/// Init the manager with the expected tick rate
///
/// @param rate The amout of ticks per call to time_mgr_tick
void time_mgr_init(uint32_t rate)
{
    ticks_elapsed = 0;
    tick_rate = rate;
}

/// Update the time manager time
/// Expected to be called with a re-occuring timer
void time_mgr_tick(void)
{
    ticks_elapsed += tick_rate;
}

/// Get the number of ms elapsed since power on
///
/// @return the ticks elapsed since power on
uint32_t time_mgr_get_ticks_elapsed(void)
{
    return ticks_elapsed;
}

/// Set a timer
///
/// @param p_timer      The timer instance
/// @param timer_ticks  The amount of time for the timer to track
void time_mgr_set_timer(time_mgr_timer_t * const p_timer,
                        uint32_t const timer_ticks)
{
    if(NULL != p_timer)
    {

        p_timer->start_ticks = timer_ticks;
        p_timer->end_ticks = timer_ticks + ticks_elapsed;
    }
}

/// Get if the timer instance is expired
///
/// @p_timer The timer instance to check
///
/// @return True if expired, false if not
bool time_mgr_get_timer_expired(time_mgr_timer_t const * const p_timer)
{
    bool ret_val = false;

    if(NULL != p_timer)
    {

        // Normal operation, no roll over expected before timer expires
        if(p_timer->start_ticks <=  p_timer->end_ticks)
        {
            ret_val = ticks_elapsed >= p_timer->end_ticks;
        }
        // Timer will expire after overflow
        else
        {
            // Check if ticks_elapsed has rolled over yet AND then compare
            // against end_ticks
            ret_val = (ticks_elapsed < p_timer->start_ticks) && ticks_elapsed <= p_timer->end_ticks;
        }

    }

    return ret_val;
}
