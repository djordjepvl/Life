#pragma once

typedef struct {
    rafgl_spritesheet_t sprites;
    rafgl_raster_t *scaled_frames;
    int *frame_flipped;
    const char *path;
} asset_t;

extern asset_t testFish;
extern asset_t testEnemyFish;
extern asset_t testBackground;

void assets_init();
void asset_init(asset_t *asset, const char *sheet_path, int sheet_width, int sheet_height);
// draw asset scaled into the provided dimensions and center coordinates
void raster_draw_scaled_asset(
    rafgl_raster_t *raster, asset_t *asset, 
    int frame_x, int frame_y,
    int width, int height,
    int x, int y,
    int horizontal_flip,
    int cheap
);

void asset_cache_frame(asset_t *asset, int index, int frame_x, int frame_y, int new_width, int new_height, int horizontal_flip, int cheap);