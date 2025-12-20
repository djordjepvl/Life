#include <main_state.h>

int game_width;
int game_height;


rafgl_raster_t raster;
rafgl_texture_t tex;

player_t player;
fish_t fish[FISH_MAX_COUNT];


float game_center_x, game_center_y;

void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    game_width = width;
    game_height = height;
    rafgl_raster_init(&raster, game_width, game_height);
    rafgl_texture_init(&tex);
    assets_init();
    
    player_init(&player, game_width/2, game_height/2, PLAYER_COLOR, &testFish);
    player.enabled = 1;
    fish_array_init();
    //fish_array_enable();

    game_center_x = game_width/2.0f;
    game_center_y = game_height/2.0f;
}


void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{
    if (game_data->keys_pressed[RAFGL_KEY_D]) fish_array_disable();
    if (game_data->keys_pressed[RAFGL_KEY_E]) fish_array_enable();
    if (game_data->keys_pressed[GLFW_KEY_R]) player_respawn(&player);
    //GAME LOGIC UPDATE
    player_update(&player, delta_time, game_data);
    fish_array_update(delta_time, game_data);

    //COLLISION CHECKS
    detect_collision(delta_time);

    //DEBUG PRINTING
    //printMousePos(game_data);

    //FILLING RASTER
    rafgl_raster_draw_rectangle(&raster,0,0,game_width,game_height,rafgl_RGB(44, 155, 219),1);
    raster_draw_scaled_asset(&raster, &testBackground, 0, 0, game_width, game_height, game_center_x, game_center_y, 0);
    
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


//COLLISION

void detect_collision(float delta_time) {
    for (int i=0; i<FISH_MAX_COUNT; i++) {
        if ( 
            fish[i].enabled &&
            player.enabled &&
            player.x-player.width/2 < fish[i].x+fish[i].width/2 &&
            player.x+player.width/2 > fish[i].x-fish[i].width/2 &&
            player.y-player.height/2 < fish[i].y+fish[i].height/2 &&
            player.y+player.height/2 > fish[i].y-fish[i].height/2
        ) {
            handle_collision(i, delta_time);
        }
    }
}

void handle_collision(int i, float delta_time) {
    if (player.size > fish[i].size) {
        fish[i].enabled = 0;
        player_set_size(&player, player.size + fish[i].size * EAT_MULTIPLIER);
    }
    else {
        player.enabled = 0;
        fish_set_size(&fish[i], fish[i].size + player.size * EAT_MULTIPLIER);
    }
}

//DEBUG:

void printMousePos(rafgl_game_data_t *game_data) {
    float x = game_data->mouse_pos_x;
    float y = game_data->mouse_pos_y;
    if (x > 0 && x < game_width && y > 0 && y < game_height)
        printf("Mouse pos : (%f, %f) \n", game_data->mouse_pos_x, game_data->mouse_pos_y);
}