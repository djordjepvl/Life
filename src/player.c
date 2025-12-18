#include <main_state.h>

void player_init(player_t *p, float x, float y) {
    p->enabled = 0;
    p->x = x;
    p->y = y;
    p->dx = 0;
    p->dy = 0;
    p->h_border_damp = 1;
    p->v_border_damp = 1;

    p->size = 130;
    p->accel =0.01;
    p->damp = 0.9995;
    p->color.rgba = rafgl_RGB(245, 183, 39);
    player_update_dimensions(p);
}

void player_update(player_t *p, float delta_time, rafgl_game_data_t *game_data) {
    if (!p->enabled) return;

    if (game_data->keys_down[GLFW_KEY_W]) {
        p->size = rafgl_clampf(p->size+0.8f, PLAYER_SIZE_START, PLAYER_SIZE_MAX);
        player_update_dimensions(p);
    }
    if (game_data->keys_down[GLFW_KEY_S]) {
        p->size = rafgl_clampf(p->size-0.8f, PLAYER_SIZE_START, PLAYER_SIZE_MAX);
        player_update_dimensions(p);
    }

    // TODO: redo physics to use delta_time

    p->v_border_damp = 
        ((p->y < border_size + border_edge) ? ( (p->y - border_edge) / border_size) : 1.0) -
        ((game_height - p->y < border_size + border_edge) ? (((game_height - p->y) - border_edge) / border_size) : 1.0);
    
    p->h_border_damp = 
        ((p->x < border_size +border_edge) ? ( (p->x - border_edge) / border_size) : 1.0f) -
        ((game_width - p->x < border_size +border_edge) ? (((game_width - p->x) - border_edge) / border_size) : 1.0f);
    
    
    float ix = 0.0, iy = 0.0;

    if (game_data->keys_down[RAFGL_KEY_UP]) {
        iy-= 1.0;
    }
    if (game_data->keys_down[RAFGL_KEY_DOWN]) {
        iy+= 1.0;
    }
    if (game_data->keys_down[RAFGL_KEY_LEFT]) {
        ix-= 1.0;
    }
    if (game_data->keys_down[RAFGL_KEY_RIGHT]) {
        ix+= 1.0;
    }

    if (ix != 0.0f || iy != 0.0f) {
        float len = sqrtf(ix*ix + iy*iy);
        ix /= len;
        iy /= len;

        float ax = ix * p->accel;
        float ay = iy * p->accel;

        float elastic = cbrtf(p->damp / p->accel);

        ax *= (1.0f - ix * p->h_border_damp*elastic);
        ay *= (1.0f - iy * p->v_border_damp*elastic);

        p->dx += ax;
        p->dy += ay;
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
    float t = 1.0f*p->size / PLAYER_SIZE_MAX;
    t = sqrtf(sqrtf(sqrtf(t)));
    
    p->accel = PLAYER_ACCEL_START + t * (PLAYER_ACCEL_END - PLAYER_ACCEL_START);
    p->damp  = PLAYER_DAMP_START  + t * (PLAYER_DAMP_END  - PLAYER_DAMP_START);
    printf("%f \n", p->accel);
}