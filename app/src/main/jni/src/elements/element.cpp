#include "element.h"

namespace scenevr {

using namespace three;

void Element::parseStyles() {
  styles = new Stylemap(node.attribute("style").value());
}

Vector3 Element::parseVector(const std::string str) {
  std::istringstream s2(str);
  Vector3 v;

  s2 >> v.x;
  s2 >> v.y;
  s2 >> v.z;

  return v;
}

}