#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "pendulum.hh"
#include "graphics.hh"

int main() {
  Graphics graphics;
  Pendulum<double> pendulum;
  bool finished = false;

  unsigned int last_tick = SDL_GetTicks();
  unsigned int remaining_ticks = 0;
  unsigned int min_ticks = 1;

  while (!finished) {
    // drain event queue
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          // XXX
          break;
        case SDL_QUIT:
          finished = true;
          break;
        default:
          break;
      }
    }

    graphics.prerender();
    graphics.render(pendulum);
    graphics.postrender();

    unsigned int now_tick = SDL_GetTicks();
    unsigned int dticks = now_tick - last_tick;
    remaining_ticks += dticks;

    while (remaining_ticks >= min_ticks) {
      const float dt = min_ticks * 1e-3;
      pendulum.step(dt);
      remaining_ticks -= min_ticks;
    }
    last_tick = now_tick;
  }

  return 0;
}
