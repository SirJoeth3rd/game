//This is the main program it handles the execution and the game loop

#include <SDL2/SDL.h>
#include "flecs.h"
#include <iostream>
#include "nevergray.hpp"
#include "vec2d.hpp"

flecs::world world; //the ecs is THE global variable

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

int main(int c, char* argv[]) {
  //init SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "SDL has been initialised" << std::endl;
  }

  auto window = init_window("nevergray",
			    SDL_WINDOWPOS_CENTERED,
			    SDL_WINDOWPOS_CENTERED,
			    SCREEN_HEIGHT,
			    SCREEN_WIDTH,
			    false);
  
  auto renderer = init_renderer(window);

  bool running = true;

  load_world(renderer);

  const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  //the game loop
  while (running) {

    frameStart = SDL_GetTicks();
    
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;

    default:
      break;
    }

    frameTime = SDL_GetTicks() - frameStart;

    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }

    render_world(renderer);    
  }

  //cleanup
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  std::cout << "Game cleaned" << std::endl;
}

void load_world(SDL_Renderer* renderer) {
  auto bob = world.entity("Bobby");

  bob.set([renderer](VisualComponent& vc) {
    vc = {
      load_texture("./assets/mushroom.png", renderer),
      BoxSize {(int) (SCREEN_WIDTH*0.1), (int) (SCREEN_HEIGHT*0.1)}
    };
  });
  //now Bobby has a visual component  
}

SDL_Texture* load_texture(const char* filename, SDL_Renderer* renderer) {
  auto surf = IMG_Load(filename);

  if (surf == NULL) {
    std::cout << "surface: " << filename << " could not be loaded" << std::endl;
  }
  
  auto vc = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(surf);
  return vc;
}

//init window and renderer might be used for some other initializations hence the functions
SDL_Window* init_window(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
  int flags = 0;

  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  auto window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

  if (window) {
    std::cout << "window initialised successfully" << std::endl;
  }
  
  return window;
}

SDL_Renderer* init_renderer(SDL_Window* window) {
  auto renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer) {
    std::cout << "renderer initialised successfully" << std::endl;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);    
  }

  return renderer;
}

//this function renders the world in the ecs onto the given renderer
void render_world(SDL_Renderer* renderer) {
  SDL_RenderClear(renderer);

  //here all rendering happens
  //let's render Bobby to the center of the screen
  auto bobby = world.lookup("Bobby");
  SDL_RenderCopy(
		 renderer,
		 bobby.get<VisualComponent>()->texture,
		 NULL,
		 NULL);
  
  SDL_RenderPresent(renderer);
}


