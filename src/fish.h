#pragma once

typedef struct {
    int enabled;
    float x, y;
    float dx, dy;
    float speed;

    float size;
    int width, height;

    rafgl_pixel_rgb_t color;
} fish_t;

extern int fish_array_enabled;


void fish_array_init();
void fish_array_update(float delta_time, rafgl_game_data_t *game_data);
void fish_array_render();

void fish_array_enable();
void fish_array_disable();

void fish_init(fish_t *f);
void fish_update(fish_t *f, float delta_time, rafgl_game_data_t *game_data);
void fish_render(fish_t *f);

void fish_random_spawn(fish_t *f);
void fish_set_size(fish_t *f, float new_size);