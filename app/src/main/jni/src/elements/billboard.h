#pragma once

#include "element.h"

namespace scenevr {

class Billboard : public Element {
  public:
    static Ptr create(pugi::xml_node node) { 
      return std::make_shared<Billboard>(node); 
    }

    Billboard(const pugi::xml_node n);
};

}
