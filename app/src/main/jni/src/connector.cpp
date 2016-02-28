#include "connector.h"

namespace scenevr {

using namespace std;

Connector::Connector(const string u) : url(u) {
  SDL_Log("Initialized connector");
}

void Connector::connect() {
  SDL_Log("Connecting to %s", url.c_str());
}

}