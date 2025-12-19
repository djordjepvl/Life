#include <main_state.h>

#define TESTFISH_W 1
#define TESTFISH_H 1
rafgl_spritesheet_t testFish;
rafgl_raster_t testFishScaledFrames[TESTFISH_H*TESTFISH_W];

void assets_init() {
    rafgl_spritesheet_init(&testFish, "res/testAlphaFish.png", TESTFISH_W, TESTFISH_H);
}