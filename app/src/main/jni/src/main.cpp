#define THREE_GLES 1

#include <string>
#include <sstream>
#include <chrono> /* C++11 functionality */
#include <random>
#include <cstdlib>
#include <assert.h>
#include <stdio.h>
#include <string>
#include <memory>
#include <thread>
#include <jni.h>

#include <SDL.h>

#include <three/three.h>
#include <three/gl.h>
#include <three/renderers/gl_renderer.h>
#include <three/renderers/renderer_parameters.h>
#include <three/scenes/scene.h>
#include <three/core/geometry.h>
#include <three/cameras/perspective_camera.h>
#include <three/lights/point_light.h>
#include <three/objects/mesh.h>
#include <three/extras/geometries/sphere_geometry.h>
#include <three/extras/geometries/box_geometry.h>
#include <three/extras/geometries/plane_geometry.h>
#include <three/materials/mesh_lambert_material.h>
#include "vendor/sdl.h"

#include "client.h"

static int Java_org_libsdl_app_SDLActivity_CreateSurfaceTexture( const int width, const int height ) {
    int glTexture;

    // glGenTextures( 1, &glTexture );

    // if ( glTexture > 0 ) {
    //     glBindTexture( GL_TEXTURE_EXTERNAL_OES, glTexture );

    //     // Notice the use of GL_TEXTURE_2D for texture creation
    //     glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 );
    //     glTexParameteri( GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    //     glTexParameteri( GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        
    //     glTexParameteri( GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    //     glTexParameteri( GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        
    //     glBindTexture( GL_TEXTURE_EXTERNAL_OES, 0 );
    // }

    return glTexture;
}

/* Must use parameters here or else there will be an undefined reference to SDL_main */
int main(int argc, char** argv)
{
    /* Initialize SDL library */
    SDL_Window* sdlWindow = 0;
    SDL_GLContext sdlGL = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initalize SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    int width = mode.w;
    int height = mode.h;

    SDL_Log("Width = %d. Height = %d\n", width, height);

    sdlWindow = SDL_CreateWindow(nullptr, 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_INIT_JOYSTICK);

    if (sdlWindow == 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create the sdlWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    sdlGL = SDL_GL_CreateContext(sdlWindow);

    three::RendererParameters params;
    three::GLWindow window(params, sdlWindow, sdlGL);
    three::GLInterface interface = window.createGLInterface();
    auto renderer = three::GLRenderer::create(params, interface);

    const GLubyte* rendererString = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    // glGetIntegerv(GL_MAJOR_VERSION, &major);
    // glGetIntegerv(GL_MINOR_VERSION, &minor);

    std::stringstream ss;
    ss << "\n-------------------------------------------------------------\n";
    ss << "GL Vendor    : " << vendor;
    ss << "\nGL GLRenderer : " << rendererString;
    // ss << "\nGL Version   : " << version;
    // ss << "\nGL Version   : " << major << "." << minor;
    ss << "\nGLSL Version : " << glslVersion;
    ss << "\n-------------------------------------------------------------\n";
    SDL_Log("%s", ss.str().c_str());

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
    //glCullFace(GL_BACK);

    /* Create OpenGL vertex data */

    auto client = new scenevr::Client(renderer, &window);
    client->connect("ws://192.168.1.8:8080/color-change.xml");
    client->start();

    /*

    // Materials
    auto material = three::MeshLambertMaterial::create(
      three::Material::Parameters()
        .add( "color", three::Color( 0xff00aa ) )
        .add( "emissive", three::Color( 0x330011 ) )
    );

    // Geometries
    auto geometry = three::BoxGeometry::create( 1, 1, 1 );

    auto box = three::Mesh::create( geometry, material );
    box->rotation().x = -M_PI / 2;
    scene->add( box );

    bool done = false;
    bool movingForward = false;

    window.addEventListener(SDL_JOYBUTTONDOWN, [&]( const SDL_Event& event ) {
      if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
        movingForward = true;
      }
    });

    window.addEventListener(SDL_JOYBUTTONUP, [&]( const SDL_Event& event ) {
      if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
        movingForward = false;
      }
    });

    window.animate( [&]( float dt ) -> bool {
      camera->position().set(0, 5, -10);
      camera->lookAt( scene->position() );

      box->rotation().y += movingForward ? 0.1 : 0.025;
      box->rotation().z += movingForward ? 0.1 : 0.025;

      renderer->render( *scene, *camera );

      return true;
    } );

    */

    SDL_Log("Exited successfully");

    return EXIT_SUCCESS;
} /* main */
