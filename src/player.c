#include <main_state.h>

void player_init(player_t *p, float x, float y) {
    p->enabled = 0;
    p->x = x;
    p->y = y;
    p->dx = 0;
    p->dy = 0;
    p->size = 30;

    p->color.rgba = rafgl_RGB(245, 183, 39);
    player_update_dimensions(p);
}

void player_update(player_t *p, float delta_time, rafgl_game_data_t *game_data) {
    if (!p->enabled) return;
    p->x += p->dx;
    p->y += p->dy;
}

void player_render(player_t *p) {
    if (!p->enabled) return;
    rafgl_raster_draw_rectangle(&raster, 
        p->x - p->width/2, p->y - p->height/2,
        p->width, p->height, p->color.rgba, 1);
}

void player_update_dimensions(player_t *p) {
    p->width = p->size;
    p->height = p->size/2;
}