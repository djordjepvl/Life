#pragma once

//OpenGL headers
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <rafgl.h>

//C headers
#include <math.h>

//Game headers
#include <game_constants.h>
#include <player.h>
#include <fish.h>

void main_state_init(GLFWwindow *window, void *args, int width, int height);
void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args);
void main_state_render(GLFWwindow *window, void *args);
void main_state_cleanup(GLFWwindow *window, void *args);

void detect_collision(float delta_time);

void printMousePos(rafgl_game_data_t *game_data);


//Main variables
extern int game_height, game_width;
extern rafgl_raster_t raster;
extern rafgl_texture_t tex;

extern player_t player;
extern fish_t fish[FISH_MAX_COUNT];


