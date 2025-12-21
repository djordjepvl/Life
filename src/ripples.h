#pragma once

/*
Ovo je manje vise simulacija pomeranja vode koja koristi 30 kruznih talasa (ripple_t) koji
se stvaraju oko igraca kad se pomera i dodavaju se jedan na drugi.

ripple_spawn_any() stvara talas na datim koordinatama x i y jacine strength koji
ima trajanje lifetime.

u ripple_update() talas se na osnovu trenutnog stanja racuna i dodaje na 
ripple_bump_map, koji je 1/8 velicine prozora igrice

nakon sto su se svi talasi dodali, u ripple_bump_map_apply() radim blur
filter nad mapom da bi talasi izgledali vise spojeno, a onda
da bi malo poboljsao rezoluciju radim box scaling u
ugnezdjenoj petlji
*/

#define RIPPLE_MAX_STRENGTH 1024
#define RIPPLE_MAX_LIFE 5.0f
#define RIPPLE_BASE_SPEED 700
#define RIPPLE_DAMP 0.96f
#define RIPPLE_SHARPNESS 6.0f
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
    int32_t x, y;
} pair_t;

#define BMAP_SHIFT 3
#define BMAP_SCALE 8
extern int bmap_width, bmap_height;
extern pair_t *ripple_bump_map;
extern rafgl_raster_t ripple_temp_raster;

void ripple_bump_map_init();
void ripple_bump_map_reset();
void ripple_bump_map_apply();