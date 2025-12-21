#include <main_state.h>

int game_width;
int game_height;


rafgl_raster_t raster;
rafgl_texture_t tex;

player_t player;
fish_t fish[FISH_MAX_COUNT];


float game_center_x, game_center_y;
float cam_x, cam_y;
float cam_target_x, cam_target_y;

void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    game_width = width;
    game_height = height;
    cam_x = cam_y = 0.0f;
    rafgl_raster_init(&raster, game_width, game_height);
    rafgl_texture_init(&tex);
    assets_init();
    
    player_init(&player, game_width/2, game_height/2, PLAYER_COLOR, &testFish);
    player.enabled = 1;
    fish_array_init();
    //fish_array_enable();

    ripple_bump_map_init();
    ripple_array_init();
    postfx_init();
    
    game_center_x = game_width/2.0f;
    game_center_y = game_height/2.0f;
}


void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{
    if (game_data->is_lmb_down) {
        ripple_spawn_any(game_data->mouse_pos_x, game_data->mouse_pos_y,
            RIPPLE_MAX_STRENGTH * 1.0f * game_data->mouse_pos_x/game_width,
            RIPPLE_MAX_LIFE * 1.0f * game_data->mouse_pos_y/game_height);
    }

    if (game_data->keys_pressed[RAFGL_KEY_D]) fish_array_disable();
    if (game_data->keys_pressed[RAFGL_KEY_E]) fish_array_enable();
    if (game_data->keys_pressed[GLFW_KEY_R]) player_respawn(&player);
    //GAME LOGIC UPDATE
    player_update(&player, delta_time, game_data);
    fish_array_update(delta_time, game_data);
    ripple_array_update(delta_time);
    postfx_wave_update(delta_time);

    //UPDATE CAMERA
    cam_target_x = (player.x - game_center_x) * CAM_FOLLOW_PLAYER;
    cam_target_y = (player.y - game_center_y) * CAM_FOLLOW_PLAYER;
    cam_x = rafgl_lerpf(cam_x, cam_target_x, CAM_SPEED);
    cam_y = rafgl_lerpf(cam_y, cam_target_y, CAM_SPEED);

    //COLLISION CHECKS
    detect_collision(delta_time);

    //DEBUG PRINTING
    //printMousePos(game_data);

    //FILLING RASTER
    raster_draw_scaled_asset(&raster, &testBackground, 0, 0, game_width*1.1f, game_height*1.1f, game_center_x+cam_x*PRLX_BG, game_center_y+cam_y*PRLX_BG, 0, 1);
    ripple_bump_map_apply();
    fish_array_render();
    player_render(&player);
    postfx_wave_render();
    return;

    // draw ripple bump map
    for (int y = 0; y < game_height; y++) {
    for (int x = 0; x < game_width; x++) {
        int indx = (x>>2) + (y>>2) * bmap_width;

        int bx = ripple_bump_map[indx].x;
        int by = ripple_bump_map[indx].y;

        int rx = (bx * 128) / 64 + 128;
        int ry = (by * 128) / 64 + 128;

        rx = rafgl_clampi(rx, 0, 255);
        ry = rafgl_clampi(ry, 0, 255);

        pixel_at_m(raster, x, y).rgba = rafgl_RGB(rx, ry, 128);
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
        player.x = game_center_x;
        player.y = game_center_y;
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