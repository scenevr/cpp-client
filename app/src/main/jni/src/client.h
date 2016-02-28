#ifndef CLIENT_H
#define CLIENT_H

#include <three/renderers/gl_renderer.h>
#include <SDL.h>
#include <SDL_events.h>
#include <functional>
#include <map>
#include <vector>

#include "connector.h"

namespace scenevr {

class Client : public three::NonCopyable {

  public:
    Client(const three::GLRenderer r);
    // ~Client();

    void connect(std::string url);
  private:
    void update();

    Connector::Ptr connector;
    three::GLRenderer renderer;
};

}

#endif
