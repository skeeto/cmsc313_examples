#ifndef GRAPHICS_HH
#define GRAPHICS_HH

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "pendulum.hh"

class Graphics {
public:
  Graphics();
  void render(const Pendulum<double> &pendulum);
  void prerender();
  void postrender();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int w = 640, h = 640;
  GLuint filled; // shaders
  GLuint verts; // vbo

  void spring_zigzag(GLfloat* dest, int n,
                     const Vec<double> &p1, const Vec<double> &p2);
};

typedef enum {
  ATTR_VERTEX
} ProgramAttributes;

#endif
