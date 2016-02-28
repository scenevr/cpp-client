#ifndef ELEMENT_H
#define ELEMENT_H

#include <three/gl.h>
#include <three/core/object3d.h>
#include <memory>
#include <pugixml.hpp>

#include "stylemap.h"

namespace scenevr {

class Element {
  public:
    typedef std::shared_ptr<Element> Ptr;
    three::Object3D::Ptr object;

  // protected:
    std::string uuid;
    pugi::xml_node node;
    Stylemap* styles;

    void parseStyles();
    three::Vector3 parseVector(const std::string str);
};

}

#endif
