#include "element.h"

namespace scenevr {

using namespace three;

Element::Element(pugi::xml_node n) : node(n) {
  parseStyles();
}

void Element::parseStyles() {
  styles = new Stylemap(node.attribute("style").value());
}

Vector3 Element::parseVector(const std::string str, Vector3 nominal) {
  Vector3 v;
  v.copy(nominal);

  if (str.empty()) {
    return v;
  }

  std::istringstream s2(str);

  s2 >> v.x;
  s2 >> v.y;
  s2 >> v.z;

  return v;
}

}