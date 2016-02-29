#include "skybox.h"

#include <three/objects/mesh.h>
#include <three/constants.h>
#include <three/extras/geometries/box_geometry.h>
#include <three/materials/mesh_basic_material.h>

namespace scenevr {

using namespace three;

Skybox::Skybox(const pugi::xml_node n) : Element(n){
  auto material = three::MeshBasicMaterial::create(
    three::Material::Parameters()
      .add("color", three::Color(styles->getPropertyValue("color")))
      .add("side", THREE::BackSide)
  );

  auto geometry = BoxGeometry::create(128, 128, 128);
  object = Mesh::create( geometry, material );
}

}