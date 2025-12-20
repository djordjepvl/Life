#include <main_state.h>

//GLOBAL

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;
const int BORDER_SIZE = 40; //MUST BE >0
const int BORDER_EDGE = 30; //MUST BE >0

//When fish 1 eats fish 2, fish 1's size is increased by fish2's size multiplied by this
const float EAT_MULTIPLIER = 0.1f;

//PLAYER

const uint32_t PLAYER_COLOR = rafgl_RGB(245, 183, 39);

const float PLAYER_ACCEL_START = 0.3f;
const float PLAYER_ACCEL_END = 0.002f;

const float PLAYER_DAMP_START = 0.99f;
const float PLAYER_DAMP_END  = 0.9993f;

const float PLAYER_START_SIZE = 30.0f;
const float PLAYER_MIN_SIZE = 30.0f;
const float PLAYER_MAX_SIZE  = 2000.0f;

//FISH

const float FISH_SPAWN_FREQUENCY = 0.2f;

const uint32_t FISH_BASE_COLOR = rafgl_RGB(235, 173, 35);
const int FISH_COLOR_VAR = 80;

const float FISH_MIN_SIZE = 15.0f;
const float FISH_MAX_SIZE = 600.0f;

const float FISH_BASE_SPEED = 820.0f;
const float FISH_SPEED_VAR = 480.0f;
const float FISH_MIN_SPEED = 0.35f;