#include <main_state.h>

asset_t testFish;
asset_t testEnemyFish;
asset_t testBackground;

void assets_init() {
    asset_init(&testFish, "res/testAlphaFish.png", 1, 1);
    asset_init(&testEnemyFish, "res/testAlphaEnemyFish.png", 1, 1);
    asset_init(&testBackground, "res/testBackground.jpg", 1, 1);
}

void asset_init(asset_t *asset, const char *sheet_path, int sheet_width, int sheet_height) {
    rafgl_spritesheet_init(&asset->sprites, sheet_path, sheet_width, sheet_height);
    asset->scaled_frames = malloc(sizeof(rafgl_raster_t) * sheet_width * sheet_height);
    for (int i=0; i<sheet_width*sheet_height; i++) rafgl_raster_init(&asset->scaled_frames[i], 0,0);
}

void raster_draw_scaled_asset(
    rafgl_raster_t *raster, asset_t *asset, 
    int frame_x, int frame_y,
    int width, int height,
    int x, int y,
    int horizontal_flip
) {
    int index = frame_x + frame_y*asset->sprites.frame_width;
    rafgl_raster_t *toDraw = &asset->scaled_frames[index];
    if (toDraw->width != width || toDraw->height != height) asset_resize_frame(asset, toDraw, frame_x, frame_y, width, height);
    rafgl_raster_draw_raster(raster, toDraw, x-width/2, y-height/2, horizontal_flip);
}

void asset_resize_frame(asset_t *asset, rafgl_raster_t *frame, int frame_x, int frame_y, int new_width, int new_height) {
    if (frame->width == new_width && frame->height == new_height) return;
    rafgl_raster_t raw;
    rafgl_raster_from_spritesheet_frame(&raw, &asset->sprites, frame_x, frame_y);
    
    rafgl_raster_cleanup(frame);
    rafgl_raster_init(frame, new_width, new_height);
    rafgl_raster_bilinear_upsample(frame, &raw);

    rafgl_raster_cleanup(&raw);
}

