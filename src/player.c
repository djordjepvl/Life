#include <main_state.h>

void player_init(player_t *p, float x, float y) {
    p->enabled = 0;
    p->x = x;
    p->y = y;
    p->dx = 0;
    p->dy = 0;
    p->size = 30;

    p->accel = 2;
    p->damp = 0.9;
    p->border_size = 40;
    p->border_edge = 30;
    p->h_border_damp = 1;
    p->v_border_damp = 1;
    p->color.rgba = rafgl_RGB(245, 183, 39);
    player_update_dimensions(p);
}

void player_update(player_t *p, float delta_time, rafgl_game_data_t *game_data) {
    if (!p->enabled) return;
    
    p->v_border_damp = 
        ((p->y < p->border_size + p->border_edge) ? ( (p->y - p->border_edge) / p->border_size) : 1.0) -
        ((game_height - p->y < p->border_size +p->border_edge) ? (((game_height - p->y) - p->border_edge) / p->border_size) : 1.0);
    
    p->h_border_damp = 
        ((p->x < p->border_size +p->border_edge) ? ( (p->x - p->border_edge) / p->border_size) : 1.0f) -
        ((game_width - p->x < p->border_size +p->border_edge) ? (((game_width - p->x) - p->border_edge) / p->border_size) : 1.0f);
    
    printf("%f \n", p->v_border_damp);
    

    if (game_data->keys_down[RAFGL_KEY_UP]) {
        p->dy-= p->accel* (1+p->v_border_damp);
    }
    if (game_data->keys_down[RAFGL_KEY_DOWN]) {
        p->dy+= p->accel* (1-p->v_border_damp);
    }
    if (game_data->keys_down[RAFGL_KEY_LEFT]) {
        p->dx-= p->accel* (1+p->h_border_damp);
    }
    if (game_data->keys_down[RAFGL_KEY_RIGHT]) {
        p->dx+= p->accel* (1-p->h_border_damp);
    }

    p->x += p->dx;
    p->y += p->dy;

    p->x -= p->h_border_damp * p->h_border_damp * p->h_border_damp * 0.7;
    p->y -= p->v_border_damp * p->v_border_damp * p->v_border_damp * 0.7;

    p->dx = p->dx*p->damp;
    p->dy = p->dy*p->damp;
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