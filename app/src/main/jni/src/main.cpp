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

#include <SDL.h>

/* Android OpenGL ES 3 headers */
#include <EGL/egl.h>
// #include <GLES3/gl3.h>
// #include <GLES3/gl3ext.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vendor/sdl.h"

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

#include <easywsclient.hpp>

/* Shader sources */
const GLchar* vertexSource =
    "#version 300 es\n"
    "precision mediump float;"
    "in vec2 aPosition;"
    "in vec3 aColor;"
    "out vec3 vColor;"
    "uniform mat4 uModel;"
    "uniform mat4 uLookAt;"
    "uniform mat4 uProjection;"
    "void main() {"
    "   vColor = aColor;"
    "   gl_Position = uProjection * uLookAt * uModel * vec4(aPosition, 0.0, 1.0);"
    "}";

const GLchar* fragmentSource =
    "#version 300 es\n"
    "precision mediump float;"
    "in vec3 vColor;"
    "out vec4 FragColor;"
    "void main() {"
    "   FragColor = vec4(vColor, 1.0);"
    "}";

using easywsclient::WebSocket;

static WebSocket::pointer ws = NULL;

void handle_message(const std::string & message)
{
    // SDL_Log(">>> %s\n", message.c_str());
}

void connectToServer() {
    SDL_Log("Thread started");

    if (!ws) {
        SDL_Log("No websocket connection");
        return;
    }

    while (ws->getReadyState() != WebSocket::CLOSED) {
        ws->poll(200);
        ws->dispatch(handle_message);
    }
}

/* Must use parameters here or else there will be an undefined reference to SDL_main */
int main(int argc, char** argv)
{
    /* Initialize SDL library */
    // SDL_Window* sdlWindow = 0;
    // SDL_GLContext sdlGL = 0;

    // if (SDL_Init(SDL_INIT_VIDEO) != 0)
    // {
    //     SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initalize SDL: %s\n", SDL_GetError());
    //     return EXIT_FAILURE;
    // }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    // SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // SDL_DisplayMode mode;
    // SDL_GetDisplayMode(0, 0, &mode);
    // int width = mode.w;
    // int height = mode.h;

    // SDL_Log("Width = %d. Height = %d\n", width, height);

    // sdlWindow = SDL_CreateWindow(nullptr, 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    // if (sdlWindow == 0)
    // {
    //     SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create the sdlWindow: %s\n", SDL_GetError());
    //     SDL_Quit();
    //     return EXIT_FAILURE;
    // }

    // sdlGL = SDL_GL_CreateContext(sdlWindow);

    three::RendererParameters params;
    three::GLWindow window(params);
    three::GLInterface interface = window.createGLInterface();
    auto renderer = three::GLRenderer::create(params, interface);

    // Camera
    auto camera = three::PerspectiveCamera::create(
      50, (float) renderer->width() / renderer->height(), .1f, 1000.f
    );
    camera->position().z = 10;


    // Scene
    auto scene = three::Scene::create();
    scene->add( camera );

    // Lights
    auto pointLight = three::PointLight::create( 0xFFFFFF );
    pointLight->position() = three::Vector3( 0.75, 1, 0.5 ).multiplyScalar(50);
    pointLight->lookAt(three::Vector3(0, 0, 0));
    scene->add( pointLight );


    // Materials
    auto material = three::MeshLambertMaterial::create(
      three::Material::Parameters().add( "color", three::Color( 0xffffff ) )
    );

    // Geometries
    auto geometry = three::PlaneGeometry::create( 64, 64 );

    auto plane = three::Mesh::create( geometry, material );
    plane->rotation().x = -M_PI / 2;
    scene->add( plane );

    bool done = false;

    window.animate( [&]( float dt ) -> bool {
      // std::lock_guard<std::mutex> guard(scene_mutex);

      //camera->position().x += (-10.f * mouseX - camera->position().x ) * 3 * dt;
      //camera->position().y = 2.0f;
      camera->position().set(0, 5, -10);
      camera->lookAt( scene->position() );

      renderer->render( *scene, *camera );

      return true;
    } );

    // while (!done)
    // {
    //     SDL_Event event;
    //     while (SDL_PollEvent(&event))
    //     {
    //         if (event.type == SDL_QUIT)
    //         {
    //             done = true;
    //         }
    //         else if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION || event.type == SDL_FINGERMOTION)
    //         {
    //             // no implementation right now
    //         }
    //     }

    //     SDL_GL_SwapWindow(sdlWindow);
    // }

    return EXIT_SUCCESS;
}
