#include <main_state.h>


ripple_t ripples[RIPPLE_COUNT];

int gaus_map[RIPPLE_MAX_STRENGTH+1][RIPPLE_MAX_STRENGTH/2];

int bmap_width, bmap_height;
pair_t *ripple_bump_map;


void ripple_array_init() {
    for (int i=0; i<RIPPLE_MAX_STRENGTH+1; i++) {
        for (int j=0; j<1+RIPPLE_MAX_STRENGTH/3; j++)
            gaus_map[i][j] = 0;
    }
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
    r->speed *= RIPPLE_DAMP;
    r->range += r->speed * delta_time;
    r->range = rafgl_min_m(r->range, RIPPLE_MAX_STRENGTH-1);
    int range = (int)r->range / 2.0f;
    int thickness = (int)(range*0.45f);
    float a = 1.0f - (float)r->age / (float)r->lifetime;
    
    if (!gaus_map[RIPPLE_MAX_STRENGTH][thickness]) {
        for (int x = range - thickness * 2; x <= range; x++) {
            float t = (float)(x - (range - thickness));
            gaus_map[x][thickness] = powf(1.4f, -t * t / (float)thickness) * (1 << 16);
        }
        gaus_map[RIPPLE_MAX_STRENGTH][thickness] = 1;
    }

    int rx = r->x / 2;
    int ry = r->y / 2;
    int r2_outer = range * range;
    int r2_inner = (range - thickness * 2) * (range - thickness * 2);

    for (int dy = -range; dy <= range; dy++) {
        int y = ry + dy;
        if (y < 0 || y >= bmap_height) continue;

        int dx_limit = (int)sqrtf(r2_outer - dy * dy);
        for (int dx = -dx_limit; dx <= dx_limit; dx++) {
            int x = rx + dx;
            if (x < 0 || x >= bmap_width) continue;

            int dist2 = dx * dx + dy * dy;
            if (dist2 < r2_inner || dist2 > r2_outer) continue;

            int dist = (int)sqrtf(dist2);
            int indx = x + y * bmap_width;



            int g = (r->amplitude * gaus_map[dist][thickness]) >> 16;

            /* approximate normalize: dx/dist, dy/dist */
            int offx = (dx * g) / (dist + 1);
            int offy = (dy * g) / (dist + 1);

            /* apply age fade */
            offx = (offx * a);
            offy = (offy * a);

            ripple_bump_map[indx].x += offx;
            ripple_bump_map[indx].y += offy;
        }
    }
}



void ripple_bump_map_init() {
    bmap_width = game_width/2;
    bmap_height = game_height/2;
    ripple_bump_map = malloc(sizeof(pair_t)*bmap_width*bmap_height);
    ripple_bump_map_reset();
}
void ripple_bump_map_reset() {
    memset(ripple_bump_map, 0, sizeof(pair_t) * bmap_width * bmap_height);
}
void ripple_bump_map_apply() {

}