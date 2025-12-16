#include "all.h"

static int w, h;
static rafgl_raster_t raster;
static rafgl_texture_t tex;


int offset[2] = {0,0};

void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    w = width;
    h = height;
    rafgl_raster_init(&raster, w, h);
    rafgl_texture_init(&tex);
    printHello();
}


void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{
    int x,y;
    for (y=0; y<h; y++){
        for (x=0; x<w; x++) {
            pixel_at_m(raster,x,y).rgba = rafgl_RGB(50,180,60);
        }
    }
}

void main_state_render(GLFWwindow *window, void *args)
{
    rafgl_texture_load_from_raster(&tex, &raster);
    rafgl_texture_show(&tex, 0);
}

void main_state_cleanup(GLFWwindow *window, void *args)
{

}
