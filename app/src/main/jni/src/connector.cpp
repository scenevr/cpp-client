#include "connector.h"
#include "elements/box.h"
#include "elements/skybox.h"

#include <thread>


namespace scenevr {

using namespace std;
using namespace easywsclient;
using namespace three;

Connector::Connector(const string u, Object3D::Ptr s) : url(u), scene(s) {
  SDL_Log("Initialized connector");
  SDL_Log("Connecting to %s", url.c_str());

  websocket = WebSocket::from_url(url);
  websocketThread = new thread(&Connector::pollWebsocket, this);
}

void Connector::handleMessage(const std::string & message) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_string(message.c_str());

  if (result) {
    std::lock_guard<std::mutex> guard(sceneMutex);

    for (auto node = doc.child("packet").first_child(); node; node = node.next_sibling()) {
      string uuid = node.attribute("uuid").value();

      if (elementMap.find(uuid) != elementMap.end()) {
        // sweet...
        continue;
      }

      Element::Ptr element;

      if (strcmp(node.name(), "box") == 0) {
        element = Box::create(node);
      } else if (strcmp(node.name(), "billboard") == 0) {
        element = Box::create(node);
      } else if (strcmp(node.name(), "skybox") == 0) {
        element = Skybox::create(node);
      } else {
        SDL_Log("Unhandled element <%s/>", node.name());
        continue;
      }

      elementMap[uuid] = element;
      scene->add(element->object);
    }
  }
}

void Connector::pollWebsocket () {
  while (websocket->getReadyState() != WebSocket::CLOSED) {
    websocket->poll(200);

    WebSocket::pointer wsp = &*websocket;
    websocket->dispatch([wsp, this](const std::string & message) {
      handleMessage(message);
    });
  }
}

}