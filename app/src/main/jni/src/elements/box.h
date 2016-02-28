#ifndef BOX_H
#define BOX_H

#include "element.h"

namespace scenevr {

class Box : public Element {
  public:
    static Ptr create(pugi::xml_node node) { 
      return std::make_shared<Box>(node); 
    }

    Box(const pugi::xml_node n);
};

}

#endif
