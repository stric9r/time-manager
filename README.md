# time-manager
Tick based time manager. Use case is a single peripheral timer ticks this module, allowing for multiple timers to be tracked for expiration.
Precision depends on how fast your main clock is.  This was tested with a 50Mhz clock source, with the timer prescaled down by 128 (or 390.625khz). 
This allowed for 1ms worth of ticks ~391 between interrupts; which allowed the 50Mhz clock to have 50k ticks (20ns per tick) to poll.

This allowed for pretty good accuracy and precision.  Keep in mind that the closer the interrupt is to the clock source the less accurate/precise this module will be.

## Use / Example

```
#include "time_mgr.h"
...
#deinfe TIMER_MGR_RATE_MS 1u
#define SEC_IN_MS 1000u
...
void main(...)
{
    // MCU specific code that setups up the MCU clock, timer with prescale, ticks to count, and enable interrupt
    // aligned with the time for X ticks.  This example assumes 1ms worth of ticks.
    mcu_clk_init(...); 
    mcu_timer_init(...);
    mcu_timer_start(...);

    // Set up how many ticks per time needed
    // Again, example setup for 1 ms
    time_mgr_init(TIMER_MGR_RATE_MS);

    // Set up first timer for 1 second
    time_mgr_timer_t delay;
    time_mgr_set_timer(&delay, SEC_IN_MS);
    
    while(true)
    {
        // Poll the timer manager module
        // Time elapsed, do something then set timer back up
        if(time_mgr_get_timer_expired(&delay))
        {
            // Do something
            // ...

            // Set timer up for next round
            time_mgr_set_timer(&delay, SEC_IN_MS);
        }
        
    }
}

/// MCU interrupt to tick the module
void TIMER_IRQ(void)
{
    time_mgr_tick();
}
```
