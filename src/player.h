#pragma once

typedef struct {
    int enabled;
    float x, y;
    float dx, dy;
    float size;
    int width, height;
    float accel, damp;

    float h_border_damp, v_border_damp;
    
    rafgl_pixel_rgb_t color;
} player_t;

void player_init(player_t *p, float x, float y, uint32_t color);
void player_update(player_t *p, float delta_time, rafgl_game_data_t *game_data);
void player_render(player_t *p);

void player_update_pos(player_t *p, float delta_time, rafgl_game_data_t *game_data);
void player_set_size(player_t *p, float new_size);
