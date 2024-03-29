#include "billboard.h"

#include <three/objects/mesh.h>
#include <three/extras/geometries/box_geometry.h>
#include <three/materials/mesh_lambert_material.h>

namespace scenevr {

using namespace three;

Billboard::Billboard(const pugi::xml_node n) : Element(n){

  auto material = three::MeshLambertMaterial::create(
    three::Material::Parameters()
      .add( "color", three::Color(0xFFFFFF) )
  );

  auto geometry = BoxGeometry::create(1, 1, 1);
  object = Mesh::create( geometry, material );

  // Set position
  object->position().copy(parseVector(node.attribute("position").value()));
  object->scale().copy(parseVector(node.attribute("scale").value(), Vector3(2, 2, 0.2)));
}

}