#include <main_state.h>

int fish_array_enabled = 0;

void fish_array_init() {
    for (int i=0; i<FISH_MAX_COUNT; i++) {
        fish_init(&fish[i], &testEnemyFish);
    }
}

void fish_array_update(float delta_time, rafgl_game_data_t *game_data) {
    for (int i=0; i<FISH_MAX_COUNT; i++) {
        fish_update(&fish[i], delta_time, game_data);
    }
}

void fish_array_render() {
    for (int i=0; i<FISH_MAX_COUNT; i++) {
        fish_render(&fish[i]);
    }
}

void fish_array_enable() {
    fish_array_enabled = 1;
}

void fish_array_disable() {
    fish_array_enabled = 0;
    for (int i=0; i<FISH_MAX_COUNT; i++) {
        fish[i].enabled = 0;
    }
}

void fish_init(fish_t *f, asset_t *main_asset) {
    f->enabled = 0;
    f->x = -0;
    f->y = -0;
    f->dx = 0;
    f->dy = 0;
    f->speed = 0;
    asset_init(&f->main_asset, main_asset->path, main_asset->sprites.sheet_width, main_asset->sprites.sheet_height);
}


void fish_update(fish_t *f, float delta_time, rafgl_game_data_t *game_data) {
    if (!fish_array_enabled) return;
   
    if (!f->enabled) {
        if (chance(delta_time*FISH_SPAWN_FREQUENCY)) {
            
            f->enabled = 1;
            fish_random_spawn(f);
        }
        else return;
    }

    f->x += f->dx * delta_time;

    //despawn fish when it leaves the screen
    if (f->dx < 0.0f && f->x < -f->width/2 - 50) f->enabled = 0;
    if (f->dx > 0.0f && f->x > game_width + f->width/2 + 50) f->enabled = 0;

}



void fish_render(fish_t *f) {
    if (!f->enabled) return;
    raster_draw_scaled_asset(&raster, &f->main_asset, 0, 0, f->width+20.0f, f->height+10.0f, f->x, f->y, (f->dx > 0.0f), 0);
}

void fish_random_spawn(fish_t *f) {
    //set color
    f->color.rgba = FISH_BASE_COLOR;
    for (int i =0; i<3; i++) 
        f->color.components[i] = rafgl_clampi(f->color.components[i]+FISH_COLOR_VAR*randf()*random_sign(), 0, 255);
    
    //set random size, speed and height
    float s = randf();
    s = s*s*s*s*s;
    fish_set_size(f, rafgl_lerpf(FISH_MIN_SIZE, FISH_MAX_SIZE, s));
    f->speed = (FISH_BASE_SPEED + FISH_SPEED_VAR*randf()*random_sign() ) * rafgl_max_m((1.0f-s), FISH_MIN_SPEED);
    f->y = randf() * game_height;

    //choose side
    if (chance(0.5f)) {
        //left side
        f->dx = f->speed;
        f->x = - f->width/2 - 50;
    }
    else {
        //right side
        f->dx = - f->speed;
        f->x = game_width + f->width/2 + 50;
    }
}

void fish_set_size(fish_t *f, float new_size) {
    f->size = rafgl_clampf(new_size, FISH_MIN_SIZE, FISH_MAX_SIZE);
    f->width = f->size;
    f->height = f->size/2;
}