#include "element.h"

namespace scenevr {

using namespace three;

Vector3 Element::parseVector(const std::string str) {
  std::istringstream s2(str);
  Vector3 v;

  s2 >> v.x;
  s2 >> v.y;
  s2 >> v.z;

  return v;  
}

}