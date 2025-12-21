#pragma once
extern float wave_time;
extern float wave_phase;

#define POSTFX_WAVE_PHASE 70.0f
#define POSTFX_WAVE_SPEED 0.5f

void postfx_wave_update(float delta_time);
void postfx_wave_render();