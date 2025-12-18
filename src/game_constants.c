#include <main_state.h>

//GLOBAL
const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 1000;
const int BORDER_SIZE = 40; //MUST BE >0
const int BORDER_EDGE = 30; //MUST BE >0

//PLAYER
const uint32_t PLAYER_COLOR = rafgl_RGB(245, 183, 39);

const float PLAYER_ACCEL_START = 6.0f;
const float PLAYER_ACCEL_END = 0.003f;

const float PLAYER_DAMP_START = 0.8f;
const float PLAYER_DAMP_END  = 0.9993f;

const float PLAYER_SIZE_START = 30.0f;
const float PLAYER_SIZE_MAX  = 2000.0f;

//FISH
const float FISH_SPAWN_FREQUENCY = 0.4f;

const uint32_t FISH_BASE_COLOR = rafgl_RGB(235, 173, 35);
const int FISH_COLOR_VAR = 80;

const float FISH_MIN_SIZE = 15.0f;
const float FISH_MAX_SIZE = 600.0f;

const float FISH_BASE_SPEED = 5.0f;
const float FISH_SPEED_VAR = 2.0f;
const float FISH_MIN_SPEED = 0.5f;