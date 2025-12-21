#include <main_state.h>


ripple_t ripples[RIPPLE_COUNT];

void ripple_array_init() {
    for (int i=0; i<RIPPLE_COUNT; i++) ripple_init(&ripples[i]);
}
void ripple_array_update(float delta_time) {
    ripple_bump_map_reset();
    for (int i=0; i<RIPPLE_COUNT; i++) {
        if (ripples[i].enabled) {
            ripple_update(&ripples[i], delta_time);
        }
    }
}
void ripple_spawn_any(int x, int y, int strength, float lifetime) {
    for (int i=0; i<RIPPLE_COUNT; i++) {
        if (!ripples[i].enabled) {
            ripple_spawn(&ripples[i], x, y, strength, lifetime);
            return;
        }
    }
} 

void ripple_init(ripple_t *r) {
    r->enabled = 0;
    r->x = 0;
    r->y = 0;
    r->age = 0;
    r->lifetime = 0;
    r->range = 0;
    r->amplitude = 0;
    r->speed = 0;
    for (int i=0; i<RIPPLE_MAX_STRENGTH; i++) r->gaus_map[i] = 0;
}


void ripple_spawn(ripple_t *r, int x, int y, int strength, float lifetime) {
    strength = rafgl_clampi(strength, 1, RIPPLE_MAX_STRENGTH);
    lifetime = rafgl_clampf(lifetime, 0.01f, RIPPLE_MAX_LIFE);
    r->enabled = 1;
    r->x = x;
    r->y = y;
    r->age = 0;
    r->lifetime = lifetime * (1 << 16);
    r->range = strength / 7.0f;
    r->amplitude = strength/2;
    r->speed = (RIPPLE_BASE_SPEED * ((float)strength / RIPPLE_MAX_STRENGTH));
    for (int i=0; i<RIPPLE_MAX_STRENGTH; i++) r->gaus_map[i] = 0;
}
void ripple_update(ripple_t *r, float delta_time) {
    if (!r->enabled) return;
    r->age += delta_time * (1 << 16);
    if (r->age >= r->lifetime) {
        r->enabled = 0;
        return;
    }
    for (int i=0; i<RIPPLE_MAX_STRENGTH; i++) r->gaus_map[i] = 0;
    r->speed *= RIPPLE_DAMP;
    r->range += r->speed * delta_time;
    r->range = rafgl_min_m(r->range, RIPPLE_MAX_STRENGTH-1);
    int range = (int)r->range;
    int thickness = (int)(r->range*0.45f);
    float a = 1.0f - (float)r->age / (float)r->lifetime;
    for (int x = range; x > range - thickness*2; x--) {
        float t = (float)(x - (range - thickness));
        r->gaus_map[x] = a * r->amplitude * powf(1.05f, -(float)t*t/(float)thickness);
    }

    int x0 = rafgl_clampi(r->x - range, 0, game_width);
    int x1 = rafgl_clampi(r->x + range, 0, game_width);
    int y0 = rafgl_clampi(r->y - range, 0, game_height);
    int y1 = rafgl_clampi(r->y + range, 0, game_height);

    for (int y=y0; y<y1; y++) {
        for (int x=x0; x<x1; x++) {
            int dx = x - r->x;
            int dy = y - r->y;
            int dist = (int)sqrtf(dx*dx + dy*dy);
            if (dist >= RIPPLE_MAX_STRENGTH) continue;
            
            int indx = x + y*game_width;
            ripple_bump_map[indx].x += r->gaus_map[dist];
            ripple_bump_map[indx].y += r->gaus_map[dist];
        }
    }
}


pair_t *ripple_bump_map;

void ripple_bump_map_init() {
    ripple_bump_map = malloc(sizeof(pair_t)*game_width*game_height);
    ripple_bump_map_reset();
}
void ripple_bump_map_reset() {
    memset(ripple_bump_map, 0, sizeof(pair_t) * game_width * game_height);
}
void ripple_bump_map_apply() {

}