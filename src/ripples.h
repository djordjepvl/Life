#pragma once


#define RIPPLE_MAX_STRENGTH 1024
#define RIPPLE_MAX_LIFE 2.0f
#define RIPPLE_BASE_SPEED 700
#define RIPPLE_DAMP 0.98f
typedef struct {
    int enabled;
    int x,y;
    int age, lifetime;
    float range;
    int amplitude;
    float speed;
    int gaus_map[RIPPLE_MAX_STRENGTH];
} ripple_t;


#define RIPPLE_COUNT 30
extern ripple_t ripples[RIPPLE_COUNT];

void ripple_array_init();
void ripple_array_update(float delta_time);
void ripple_spawn_any(int x, int y, int strength, float lifetime);

void ripple_init(ripple_t *r);
void ripple_spawn(ripple_t *r, int x, int y, int strength, float lifetime);
void ripple_update(ripple_t *r, float delta_time);


typedef struct {
    int x, y;
} pair_t;

extern pair_t *ripple_bump_map;
extern pair_t *ripple_full_bump_map;

void ripple_bump_map_init();
void ripple_bump_map_reset();
void ripple_bump_map_apply();