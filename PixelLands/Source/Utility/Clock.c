#include "Clock.h"

#include <time.h>
#ifdef _WIN32
    #include <windows.h>
#endif

static inline double fmax(double a, double b) {
    return (a > b) ? a : b;
}

uint64_t Clock_GetCurrentTime() {
#ifdef _WIN32
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return time.QuadPart;
#endif
}



uint64_t Clock_GetFrequency() {
#ifdef _WIN32
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return freq.QuadPart;
#endif
}

bool Clock_Create(Clock* clock) {
    if (!clock) return false;

    clock->frequency = Clock_GetFrequency();

    clock->current_time = Clock_GetCurrentTime();
    clock->last_time = clock->current_time;

    clock->delta_time = 0.0f;
    clock->total_time = 0.0f;
    
    clock->fps = 0.0f;
    clock->frame_count = 0;
    clock->fps_update_interval = 1.0f; 
    clock->fps_accumulator = 0.0f;

    //clock->frame_time_ms = 0.0;
    //clock->max_frame_time = 0.0;
    //clock->min_frame_time = DBL_MAX;

    clock->time_scale = 1.0f;
    clock->is_paused = false;

    return true;
}


void Clock_Pause(Clock*  clock) {
    if (clock) clock->is_paused = true;
}
void Clock_Resume(Clock*  clock) {
    if (clock) clock->is_paused = false;
}

void Clock_SetScale(Clock* clock, double scale) {
    if (clock) clock->time_scale = fmax(0.0, scale);
}


void Clock_Tick(Clock* clock) {
    if (!clock || clock->is_paused) return;
    clock->last_time = clock->current_time;
    clock->current_time = Clock_GetCurrentTime();

    double raw_dt = (double)(clock->current_time - clock->last_time) / clock->frequency;
    clock->delta_time = raw_dt * clock->time_scale;
    clock->total_time += clock->delta_time;

    clock->frame_count++;
    clock->fps_accumulator += clock->delta_time;
    if (clock->fps_accumulator >= clock->fps_update_interval) {
        clock->fps = clock->frame_count / clock->fps_accumulator;
        clock->fps_accumulator = 0.0;
        clock->frame_count = 0;
    }
}

double Clock_GetElapsedTime(Clock* clock) {
    if (!clock) return INVALID_TIME_VALUE_F;
    return clock->total_time;
}