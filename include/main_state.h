#pragma once

//OpenGL headers
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <rafgl.h>

//C headers
#include <math.h>

//Game headers
#include <game_constants.h>
#include <assets.h>
#include <player.h>
#include <fish.h>
#include <ripples.h>
#include <postfx.h>

//Main state functions
void main_state_init(GLFWwindow *window, void *args, int width, int height);
void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args);
void main_state_render(GLFWwindow *window, void *args);
void main_state_cleanup(GLFWwindow *window, void *args);

void detect_collision(float delta_time);
void handle_collision(int i, float delta_time);

void printMousePos(rafgl_game_data_t *game_data);


//Main state variables
extern int game_height, game_width;
extern float cam_x, cam_y;
#define CAM_SPEED 0.1f
#define CAM_FOLLOW_PLAYER 0.2f
#define PRLX_BG 0.3f
#define PRLX_FG 0.8f

extern rafgl_spritesheet_t testsprite;
extern rafgl_raster_t raster;
extern rafgl_texture_t tex;

extern player_t player;
extern fish_t fish[FISH_MAX_COUNT];


