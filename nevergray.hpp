#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "flecs.h"
#include <iostream>
#include "vec2d.hpp"

struct BoxSize {
  int w; 
  int h;
};

//this component stores visual information
struct VisualComponent {
  SDL_Texture* texture;
  BoxSize size;
};

//this component stores positional information
struct PositionalComponent {
  vec2d position;
  BoxSize boundary;
};

SDL_Window* init_window(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
SDL_Renderer* init_renderer(SDL_Window* window);
void render_world(SDL_Renderer*);
void load_world(SDL_Renderer*);
SDL_Texture* load_texture(const char* filename, SDL_Renderer* renderer);
