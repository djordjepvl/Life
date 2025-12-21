#include <main_state.h>


ripple_t ripples[RIPPLE_COUNT];

void ripple_array_init() {
    for (int i=0; i<RIPPLE_COUNT; i++) ripple_init(&ripples[i]);
}
void ripple_array_update(float delta_time) {
    for (int i=0; i<RIPPLE_COUNT; i++) {
        if (ripples[i].enabled) {
            ripple_update(&ripples[i], delta_time);
        }
    }
}
void ripple_spawn_any(int x, int y, int size, int lifetime) {
    for (int i=0; i<RIPPLE_COUNT; i++) {
        if (!ripples[i].enabled) {
            ripple_spawn(&ripples[i], x, y, size, lifetime);
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
    r->max_range = 0;
    r->amplitude = 0;
    r->speed = 0;
    r->gaus_map = NULL;
}
void ripple_spawn(ripple_t *r, int x, int y, int size, int lifetime) {
    printf("spawned ripple at x=%i, y=%i\n", x, y);
}
void ripple_update(ripple_t *r, float delta_time) {

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