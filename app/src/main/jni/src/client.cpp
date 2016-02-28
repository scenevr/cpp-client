#include "client.h"

namespace scenevr {

using namespace three;
using namespace std;

Client::Client(const GLRenderer r) : renderer(r) {
  SDL_Log("Initialized client");
}

void Client::connect(string url) {
  connector = Connector::create(url);
  connector->connect();
}

}