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
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    sdlWindow = SDL_CreateWindow(nullptr, 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    if (sdlWindow == 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create the sdlWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    sdlGL = SDL_GL_CreateContext(sdlWindow);

    /* Query OpenGL device information */
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    // glGetIntegerv(GL_MAJOR_VERSION, &major);
    // glGetIntegerv(GL_MINOR_VERSION, &minor);

    std::stringstream ss;
    ss << "\n-------------------------------------------------------------\n";
    ss << "GL Vendor    : " << vendor;
    ss << "\nGL GLRenderer : " << renderer;
    // ss << "\nGL Version   : " << version;
    // ss << "\nGL Version   : " << major << "." << minor;
    ss << "\nGLSL Version : " << glslVersion;
    ss << "\n-------------------------------------------------------------\n";
    // SDL_Log("%s", ss.str().c_str());

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
    //glCullFace(GL_BACK);

    /* Create OpenGL vertex data */

    return EXIT_SUCCESS;
} /* main */
