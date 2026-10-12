# Life
A simple 2D OpenGL game for our computer graphics course.
The classic "you are a fish, avoid bigger fish and eat smaller fish" type of game.
Has some cool wave effects and a bit of a Frutiger Aero style.
Built on top of a simple, custom OpenGL wrapper we were given to make a 2D game with, using pixel art.
However, because I ended up using higher resolution images, which it wasn't built to handle, the game does lag a bit.
I made some optimizations to it in order to reduce the lag. It improved a lot, but it's still not perfect since the wrapper doesn't use the GPU for rendering.

## Controls

| Input | Action |
|---|---|
| `Arrow keys` | Move player |
| `E` / `D` | Enable / Disable other fish |
| `R` | Respawn player |
| Right click | Spawn a wave |
| `W` / `S` | Grow / Shrink player (cheating) | 
