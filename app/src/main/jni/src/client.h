#ifndef CLIENT_H
#define CLIENT_H

#include <three/scenes/scene.h>
#include <three/cameras/perspective_camera.h>
#include <three/renderers/gl_renderer.h>
#include <SDL.h>
#include <SDL_events.h>
#include <functional>
#include <map>
#include <vector>
#include <mutex>

#include "connector.h"
#include "vendor/sdl.h"

namespace scenevr {

class Client : public three::NonCopyable {

  public:
    Client(three::GLRenderer::Ptr r, three::GLWindow* w);
    // ~Client();

    void connect(std::string url);
    void start();
  private:
    void update();
    bool tick(float dt);
    void createScene();

    Connector::Ptr connector;

    three::Vector3 motion;
    three::GLRenderer::Ptr renderer;
    three::GLWindow* window;
    three::Scene::Ptr scene;
    three::PerspectiveCamera::Ptr camera;
};

}

#endif
