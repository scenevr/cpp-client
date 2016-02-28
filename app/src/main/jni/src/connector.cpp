#include "connector.h"

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

  SDL_Log(">>> %s\n", message.c_str());
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