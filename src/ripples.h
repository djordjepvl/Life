#pragma once


#define RIPPLE_MAX_LEN 800
#define RIPPLE_MAX_LIFE 5.0f
typedef struct {
    int enabled;
    int x,y;
    int age, lifetime;
    int range, max_range;
    int amplitude;
    int speed;
    int gaus_map[RIPPLE_MAX_LEN];
} ripple_t;


#define RIPPLE_COUNT 1
extern ripple_t ripples[RIPPLE_COUNT];

void ripple_array_init();
void ripple_array_update(float delta_time);
void ripple_spawn_any(int x, int y, int size, float lifetime);

void ripple_init(ripple_t *r);
void ripple_spawn(ripple_t *r, int x, int y, int size, float lifetime);
void ripple_update(ripple_t *r, float delta_time);


typedef struct {
    int x, y;
} pair_t;

extern pair_t *ripple_bump_map;

void ripple_bump_map_init();
void ripple_bump_map_reset();
void ripple_bump_map_apply();