#include <main_state.h>

void player_init(player_t *p, float x, float y, uint32_t color, asset_t *main_asset) {
    p->enabled = 0;
    p->x = x;
    p->y = y;
    p->dx = 0;
    p->dy = 0;
    p->h_border_damp = 1;
    p->v_border_damp = 1;
    player_set_size(p, PLAYER_START_SIZE);


    p->color.rgba = color;
    p->main_asset = *main_asset;
    p->horizontal_flip = 0;
    p->ripple_timer = PLAYER_RIPPLE_FREQUENCY;
    
}

void player_update(player_t *p, float delta_time, rafgl_game_data_t *game_data) {
    player_update_pos(p, delta_time, game_data);
    float speed = sqrtf(p->dx * p->dx + p->dy * p->dy);
    if (speed < 0.2f) return;
    p->ripple_timer -= delta_time;
    if (p->ripple_timer<0.0f) {
        ripple_spawn_any(p->x, p->y, rafgl_max_m(100 + p->size * speed/2, 200), 1.5f - speed/10 );
        p->ripple_timer = PLAYER_RIPPLE_FREQUENCY;
    }
}

void player_render(player_t *p) {
    if (!p->enabled) return;
    if (p->width > 1000)
        raster_draw_scaled_asset(&raster, &p->main_asset, 0, 0, p->width+20.0f, p->height+10.0f, p->x, p->y, p->horizontal_flip, 0);
    else
        raster_draw_scaled_asset(&raster, &p->main_asset, 0, 0, p->width+20.0f, p->height+10.0f, p->x, p->y, p->horizontal_flip, 1);
}



void player_update_pos(player_t *p, float delta_time, rafgl_game_data_t *game_data) {
    if (!p->enabled) return;

    if (game_data->keys_down[GLFW_KEY_W]) player_set_size(p, p->size*1.1f);
    if (game_data->keys_down[GLFW_KEY_S]) player_set_size(p, p->size/1.1f);
    

    const float BASE_FPS = 240.0f;
    float frame_scale = delta_time * BASE_FPS;

    p->v_border_damp = 
        ((p->y < BORDER_SIZE + BORDER_EDGE) ? ( (p->y - BORDER_EDGE) / BORDER_SIZE) : 1.0) -
        ((game_height - p->y < BORDER_SIZE + BORDER_EDGE) ? (((game_height - p->y) - BORDER_EDGE) / BORDER_SIZE) : 1.0);
    
    p->h_border_damp = 
        ((p->x < BORDER_SIZE + BORDER_EDGE) ? ( (p->x - BORDER_EDGE) / BORDER_SIZE) : 1.0f) -
        ((game_width - p->x < BORDER_SIZE + BORDER_EDGE) ? (((game_width - p->x) - BORDER_EDGE) / BORDER_SIZE) : 1.0f);
    
    
    float ix = 0.0, iy = 0.0;

    if (game_data->keys_down[RAFGL_KEY_UP]) {
        iy-= 1.0;
    }
    if (game_data->keys_down[RAFGL_KEY_DOWN]) {
        iy+= 1.0;
    }
    if (game_data->keys_down[RAFGL_KEY_LEFT]) {
        ix-= 1.0;
        p->horizontal_flip = 0;
    }
    if (game_data->keys_down[RAFGL_KEY_RIGHT]) {
        ix+= 1.0;
        p->horizontal_flip = 1;
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

        p->dx += ax * frame_scale;
        p->dy += ay * frame_scale;
    }

    p->x += p->dx * frame_scale;
    p->y += p->dy * frame_scale;

    p->x -= p->h_border_damp * p->h_border_damp * p->h_border_damp * 0.7 * frame_scale;
    p->y -= p->v_border_damp * p->v_border_damp * p->v_border_damp * 0.7 * frame_scale;

    float damp_dt = powf(p->damp, frame_scale);
    p->dx *= damp_dt;
    p->dy *= damp_dt;
}


void player_set_size(player_t *p, float new_size) {
    p->size = rafgl_clampf(new_size, PLAYER_MIN_SIZE, PLAYER_MAX_SIZE);
    p->width = p->size;
    p->height = p->size/2;
    float t = 1.0f*p->size / PLAYER_MAX_SIZE;
    t = 1.0f - powf(0.5f, t * 19.0f);
    
    p->accel = PLAYER_ACCEL_START + t * (PLAYER_ACCEL_END - PLAYER_ACCEL_START);
    p->damp  = PLAYER_DAMP_START  + t * (PLAYER_DAMP_END  - PLAYER_DAMP_START);
}

void player_respawn(player_t *p) {
    player_init(p, 1.0f * game_width/2, 1.0f * game_height/2, p->color.rgba, &p->main_asset);
    p->enabled = 1;
}