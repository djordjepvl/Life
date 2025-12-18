#include <main_state.h>

int game_width;
int game_height;

rafgl_raster_t raster;
rafgl_texture_t tex;

player_t player;
fish_t fish[FISH_MAX_COUNT];


void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    game_width = width;
    game_height = height;
    rafgl_raster_init(&raster, game_width, game_height);
    rafgl_texture_init(&tex);
    
    player_init(&player, game_width/2, game_height/2, PLAYER_COLOR);
    player.enabled = 1;
    fish_array_init();
    fish_array_enable();
}


void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{
    //GAME LOGIC UPDATE
    player_update(&player, delta_time, game_data);
    fish_array_update(delta_time, game_data);

    
    //DEBUG PRINTING
    //printMousePos(game_data);

    //FILLING RASTER
    rafgl_raster_draw_rectangle(&raster,0,0,game_width,game_height,rafgl_RGB(44, 155, 219),1);
    fish_array_render();
    player_render(&player);
}

void main_state_render(GLFWwindow *window, void *args)
{
    rafgl_texture_load_from_raster(&tex, &raster);
    rafgl_texture_show(&tex, 0);
}

void main_state_cleanup(GLFWwindow *window, void *args)
{

}

//DEBUG:

void printMousePos(rafgl_game_data_t *game_data) {
    float x = game_data->mouse_pos_x;
    float y = game_data->mouse_pos_y;
    if (x > 0 && x < game_width && y > 0 && y < game_height)
        printf("Mouse pos : (%f, %f) \n", game_data->mouse_pos_x, game_data->mouse_pos_y);
}