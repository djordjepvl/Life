#pragma once

typedef struct {
    int enabled;
    int x,y;
    int age, lifetime;
    int range, max_range;
    int amplitude;
    int speed;
    int *gaus_map;
} ripple_t;

#define RIPPLE_COUNT 20
extern ripple_t ripples[RIPPLE_COUNT];

void ripple_array_init();
void ripple_array_update(float delta_time);

void ripple_init(ripple_t *r);
void ripple_spawn(ripple_t *r,int size, int lifetime);
void ripple_update(ripple_t *r, float delta_time);


typedef struct {
    int x, y;
} pair_t;

extern pair_t *ripple_bump_map;

void ripple_bump_map_init();
void ripple_bump_map_render();