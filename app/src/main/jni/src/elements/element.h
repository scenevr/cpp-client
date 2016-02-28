#ifndef ELEMENT_H
#define ELEMENT_H

#include <three/gl.h>
#include <three/core/object3d.h>
#include <memory>
#include <pugixml.hpp>

namespace scenevr {

class Element {
  public:
    typedef std::shared_ptr<Element> Ptr;
    three::Object3D::Ptr object;

  // protected:
    std::string uuid;
    pugi::xml_node node;

    three::Vector3 parseVector(const std::string str);
};

}

#endif
