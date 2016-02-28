#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <SDL.h>
#include <memory>
#include <thread>
#include <mutex>
#include <easywsclient.hpp>
#include <three/core/object3d.h>
#include <pugixml.hpp>

#include "elements/element.h"

namespace scenevr {

class Connector {

  public:
    typedef std::shared_ptr<Connector> Ptr;

    static Ptr create(std::string url, three::Object3D::Ptr o) { 
      return std::make_shared<Connector>(url, o); 
    }

    Connector(const std::string url, three::Object3D::Ptr sceneObject);
    // ~Connector();

  private:
    void pollWebsocket();
    void handleMessage(const std::string & message);

    std::map<std::string, std::shared_ptr<Element>> elementMap;
    std::string url;
    std::mutex sceneMutex;
    std::thread *websocketThread;
    three::Object3D::Ptr scene;
    easywsclient::WebSocket::pointer websocket = NULL;
};

}

#endif
