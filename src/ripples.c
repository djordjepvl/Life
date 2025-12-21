#include <main_state.h>


ripple_t ripples[RIPPLE_COUNT];

void ripple_array_init() {

}
void ripple_array_update(float delta_time) {

}

void ripple_init(ripple_t *r) {

}
void ripple_spawn(ripple_t *r,int size, int lifetime) {

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