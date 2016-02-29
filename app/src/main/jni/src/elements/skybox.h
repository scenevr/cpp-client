#pragma once

#include "element.h"

namespace scenevr {

class Skybox : public Element {
  public:
    static Ptr create(pugi::xml_node node) { 
      return std::make_shared<Skybox>(node); 
    }

    Skybox(const pugi::xml_node n);
};

}
