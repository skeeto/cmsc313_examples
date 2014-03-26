#include <iostream>
#include <stdexcept>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "graphics.hh"
#include "pendulum.hh"

const double kPi = 3.14159265358979323846;

// macro to run a command followed by a call to gl_check
#define GL_CHECK(x) x; gl_check(#x)

/* Report any pending OpenGL error messages. */
void gl_check(const char * msg) {
  GLenum error = glGetError();
  if(error == GL_NO_ERROR) return;

  const char* e_msg;
  switch(error) {
  case GL_INVALID_ENUM:
    e_msg = "GL_INVALID_ENUM";
    break;
  case GL_INVALID_VALUE:
    e_msg = "GL_INVALID_VALUE";
    break;
  case GL_INVALID_OPERATION:
    e_msg = "GL_INVALID_OPERATION";
    break;
  case GL_OUT_OF_MEMORY:
    e_msg = "GL_OUT_OF_MEMORY";
    break;
  default:
    e_msg = "unknown";
  }
  std::cerr << "GL_ERROR: " << msg << " => " << e_msg << std::endl;
}

GLuint shader_compile(const char* shader_src, GLenum kind) {
  GLuint shader = glCreateShader(kind);
  GL_CHECK(glShaderSource(shader, 1, &shader_src, NULL));
  GL_CHECK(glCompileShader(shader));

  int status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if(status == GL_FALSE) {
    char buffer[1024];
    int length;
    glGetShaderInfoLog(shader, sizeof(buffer), &length, buffer);
    fprintf(stderr, "compile error: %s\n", buffer);
    exit(1);
  }

  return shader;
}

GLuint shader_link(const char* vertex_src, const char* fragment_src) {
  GLuint program = glCreateProgram();
  GLuint vertex = shader_compile(vertex_src, GL_VERTEX_SHADER);
  GLuint fragment = shader_compile(fragment_src, GL_FRAGMENT_SHADER);

  GL_CHECK(glAttachShader(program, vertex));
  GL_CHECK(glAttachShader(program, fragment));

  GL_CHECK(glLinkProgram(program));

  int status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if(status == GL_FALSE) {
    char buffer[1024];
    int length;
    glGetProgramInfoLog(program, sizeof(buffer), &length, buffer);
    fprintf(stderr, "link error: %s\n", buffer);
    exit(1);
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return program;
}

Graphics::Graphics() {
  SDL_RendererInfo info;
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_OPENGL, &window, &renderer);

  // verify opengl support
  SDL_GetRendererInfo(renderer, &info);
  if(!(info.flags & SDL_RENDERER_ACCELERATED) ||
     !(info.flags & SDL_RENDERER_TARGETTEXTURE)) {
    throw std::runtime_error("context failed");
  }
  SDL_GL_CreateContext(window);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // some standard opengl choices
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_LINE_SMOOTH);

  glViewport(0, 0, w, h);

  // compile some shaders
  char solid_vs[] =
    "attribute vec2 vertex;"
    "void main(void) {"
    "  gl_Position = vec4(vertex, 0, 1);"
    "}";

  char solid_fs[] =
    "void main(void) {"
    "  gl_FragColor = vec4(1, 1, 1, 1);"
    "}";

  filled = shader_link(solid_vs, solid_fs);
  GL_CHECK(glBindAttribLocation(filled, ATTR_VERTEX, "vertex"));

  // initialize VBOs
  glGenBuffers(1, &verts);
}

void Graphics::prerender() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::postrender() {
  SDL_GL_SwapWindow(window);
}

void Graphics::spring_zigzag(GLfloat* dest, int n,
                             const Vec<double> &p1, const Vec<double> &p2) {
  auto p = p1;
  float step = p1.dist(p2) / (n - 1);
  int idx = 0;

  auto tangent = p2 - p1;
  tangent = tangent.scale(step / tangent.magnitude());

  float t_ang = tangent.angle();
  float n_ang = t_ang + kPi / 2;
  Vec<double> normal {n_ang};
  normal = normal.scale(0.01);

  dest[idx++] = p.x;
  dest[idx++] = p.y;

  for(int i = 1; i < n-1; i++) {
    Vec<double> np {0, 0};
    p = p + tangent;

    if(i % 2 == 0) {
      np = normal;
    } else {
      np = normal.scale(-1);
    }

    np = np + p;
    dest[idx++] = np.x;
    dest[idx++] = np.y;
  }

  dest[idx++] = p2.x;
  dest[idx++] = p2.y;
}

void Graphics::render(const Pendulum<double> &p) {
  GLfloat points[400];

  spring_zigzag(&points[0], 100, p.anchor, p.p1.position);
  spring_zigzag(&points[200], 100, p.p1.position, p.p2.position);

  glUseProgram(filled);

  glEnableVertexAttribArray(ATTR_VERTEX);
  glBindBuffer(GL_ARRAY_BUFFER, verts);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(ATTR_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glDrawArrays(GL_LINE_STRIP, 0, sizeof(points) / (sizeof(GLfloat) * 2));
  glDisableVertexAttribArray(ATTR_VERTEX);
}
