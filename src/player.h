#pragma once

typedef struct {
    int enabled;
    float x, y;
    float dx, dy;
    float size;
    int width, height;
    
    rafgl_pixel_rgb_t color;
} player_t;

void player_init(player_t *p, float x, float y);
void player_update(player_t *p, float delta_time, rafgl_game_data_t *game_data);
void player_render(player_t *p);
void player_update_dimensions(player_t *p);