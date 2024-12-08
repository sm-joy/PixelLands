#ifndef TIME_STEP_H
#define TIME_STEP_H

#include <stdint.h>
#include <stdbool.h>

#define INVALID_TIME_VALUE_F -1.0f

typedef struct {
    uint64_t current_time;
    uint64_t last_time;
    uint64_t frequency;

    double delta_time;
    double total_time;
    
    double fps;
    uint64_t frame_count;  
    double fps_update_interval; 
    double fps_accumulator;

    //double frame_time_ms;   
    //double max_frame_time; 
    //double min_frame_time; 

    double time_scale;
    bool is_paused; 
} Clock;

bool Clock_Create(Clock* clock);
void Clock_Tick(Clock* clock);
uint64_t Clock_GetCurrentTime();
double Clock_GetElapsedTime(Clock* clock);
uint64_t Clock_GetFrequency();
void Clock_Pause(Clock*  clock);
void Clock_Resume(Clock*  clock);
void Clock_SetScale(Clock* clock, double scale);

#endif // TIME_STEP_H