#include "box.h"

#include <three/objects/mesh.h>
#include <three/extras/geometries/box_geometry.h>
#include <three/materials/mesh_lambert_material.h>

namespace scenevr {

using namespace three;

Box::Box(const pugi::xml_node n){
  node = n;

  auto material = three::MeshLambertMaterial::create(
    three::Material::Parameters()
      .add( "color", three::Color( 0xff00aa ) )
      .add( "emissive", three::Color( 0x330011 ) )
  );

  auto geometry = BoxGeometry::create(1, 1, 1);
  object = Mesh::create( geometry, material );

  // Set position
  object->position().copy(parseVector(node.attribute("position").value()));
}

}