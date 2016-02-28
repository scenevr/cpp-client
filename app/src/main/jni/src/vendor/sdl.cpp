#include "sdl.h"

#include "three/console.h"
#include "three/core/clock.h"
#include "three/renderers/renderer_parameters.h"
#include "three/renderers/gl_renderer.h"

// TODO(jdduke): Include gles where appropriate.
#include <SDL_assert.h>
#include <SDL_timer.h>

#define M_CONC(A, B) M_CONC_(A, B)
#define M_CONC_(A, B) A##B

using namespace three;

namespace three {
namespace {

struct SDLGLInterface : public GLInterface {
  SDLGLInterface() {
#define GL_FUNC_DECL(PFUNC, FUNC) FUNC = gl ## FUNC;
#if defined(__APPLE__) || defined(THREE_GLES)
#define GL_FUNC_EXT_DECL(PFUNC, FUNC) GL_FUNC_DECL(PFUNC, FUNC)
#else
#define GL_FUNC_EXT_DECL(PFUNC, FUNC) FUNC = (PFUNC) SDL_GL_GetProcAddress("gl" #FUNC);
#endif
#include "three/gl_functions.h"
#undef GL_FUNC_DECL
#undef GL_FUNC_EXT_DECL
  }
};

} // namepace

GLWindow::GLWindow( const RendererParameters& parameters, SDL_Window* w, SDL_GLContext c) : window(w), context(c) {
  SDL_Log("GLWindow created");
}

GLWindow::~GLWindow() {
  if ( context )
    SDL_GL_DeleteContext( context );
  if ( window )
    SDL_DestroyWindow( window );
}

three::GLInterface GLWindow::createGLInterface() {
  return SDLGLInterface();
}

void GLWindow::animate( Update update ) {
  SDL_assert( valid() );

/*
  RendererParameters statsRendererParams;
  statsRendererParams.preserveDrawingBuffer = true;
  auto statsRenderer = GLRenderer::create( statsRendererParams, createGLInterface() );
  Stats stats( *statsRenderer );
*/
  Clock clock;

  auto lastUpdateTime = clock.getElapsedTime();

  while ( true ) {
    // SDL_Log("In loop");

    const auto currentTime = clock.getElapsedTime();
    const auto deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    if ( !processEvents() )
      return;

    if ( !update( deltaTime ) )
      return;

    // stats.update( deltaTime, renderStats );

    // SDL_Log("Calling #swapBuffers");
    swapBuffers();
  }
}

bool GLWindow::valid() const {
  return window && context;
}

void GLWindow::swapBuffers() {
  SDL_GL_SwapWindow( window );
}

void GLWindow::openJoysticks() {
  for( int i=0; i < SDL_NumJoysticks(); i++ ) {
    SDL_Joystick *joystick;

    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(i);
    SDL_Log("    %s\n", SDL_JoystickName(joystick));
  }
}

bool GLWindow::processEvents() {
  SDL_Event event;

  while ( SDL_PollEvent( &event ) ) {
    // SDL_Log("Event: %d", event.type);

    if ( event.type == SDL_QUIT )
      return false;

    if (event.type == SDL_JOYDEVICEADDED) {
      SDL_Log("Joystick added!");
      openJoysticks();
    }

    // if (event.type == SDL_JOYBUTTONDOWN) {
    //   SDL_Log("Button down: %d", event.jbutton.button);

    //   if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
    //     SDL_Log("A Button!");
    //   }
    //   if (event.jbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) {
    //     SDL_Log("Right shoulder!");
    //   }
    // }

    if ( event.type == SDL_KEYDOWN ) {
      switch ( event.key.keysym.sym ) {
        case SDLK_q:
        case SDLK_ESCAPE:
          return false;
        default:
          renderStats = !renderStats;
          break;
      };
    }

    auto type = (unsigned int)event.type;
      
    auto eventTypeListenersIt = listeners.find( type  );
    if ( eventTypeListenersIt == listeners.end() ) {
      continue;
    }
      
    for ( const auto& listener : eventTypeListenersIt->second ) {
      listener( event );
    }
  }
  return true;
}

} // namespace three_examples

