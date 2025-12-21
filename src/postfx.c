#include <main_state.h>

float wave_time = 0.0f;

void postfx_wave_update(float delta_time) {
    wave_time += delta_time;
    if (wave_time > POSTFX_WAVE_PHASE) wave_time -= POSTFX_WAVE_PHASE;
}

void postfx_wave_render() {
    rafgl_raster_t original;
    rafgl_raster_init(&original, game_height, game_width);
    rafgl_raster_copy(&original, &raster);

    for (int y = 0; y < game_height; y++) {
        for (int x = 0; x < game_width; x++) {
            int offset_x = (int)(10.0f * sinf((float)y / POSTFX_WAVE_PHASE + wave_time * POSTFX_WAVE_SPEED));
            int offset_y = (int)(10.0f * cosf((float)x / POSTFX_WAVE_PHASE + wave_time * POSTFX_WAVE_SPEED));

            int nx = rafgl_clampi(x + offset_x, 0, game_width - 1);
            int ny = rafgl_clampi(y + offset_y, 0, game_height - 1);

            pixel_at_m(raster, x, y) = pixel_at_m(original, nx, ny);
        }
    }
}

