#include <main_state.h>
#include <math.h>

float wave_time = 0.0f;

rafgl_raster_t postfx_temp_raster;

int *wave_offset_x_cache = NULL;
int *wave_offset_y_cache = NULL;

void postfx_init() {
    rafgl_raster_init(&postfx_temp_raster, game_height, game_width);

    wave_offset_x_cache = malloc(sizeof(int) * game_height);
    wave_offset_y_cache = malloc(sizeof(int) * game_width);
}

void postfx_wave_update(float delta_time) {
    wave_time += delta_time;
    if (wave_time > POSTFX_WAVE_PHASE) wave_time -= POSTFX_WAVE_PHASE;

    for (int y = 0; y < game_height; y++) {
        wave_offset_x_cache[y] = (int)(10.0f * sinf((float)y / POSTFX_WAVE_PHASE + wave_time * POSTFX_WAVE_SPEED));
    }

    for (int x = 0; x < game_width; x++) {
        wave_offset_y_cache[x] = (int)(10.0f * cosf((float)x / POSTFX_WAVE_PHASE + wave_time * POSTFX_WAVE_SPEED));
    }
}

void postfx_wave_render() {
    rafgl_raster_copy(&postfx_temp_raster, &raster);

    for (int y = 0; y < game_height; y++) {
        int offset_x = wave_offset_x_cache[y];

        for (int x = 0; x < game_width; x++) {
            int offset_y = wave_offset_y_cache[x];

            int nx = rafgl_clampi(x + offset_x, 0, game_width - 1);
            int ny = rafgl_clampi(y + offset_y, 0, game_height - 1);

            pixel_at_m(raster, x, y) = pixel_at_m(postfx_temp_raster, nx, ny);
        }
    }
}