#include "client.h"

#include <three/lights/point_light.h>
#include <three/extras/geometries/plane_geometry.h>
#include <three/objects/mesh.h>
#include <three/materials/mesh_lambert_material.h>
#include <three/core/object3d.h>
#include <cassert>

namespace scenevr {

using namespace three;
using namespace std;

Client::Client(GLRenderer::Ptr r, GLWindow* w) : renderer(r), window(w) {
  SDL_Log("Initialized client");
  createScene();
}

void Client::connect(string url) {
  auto object = Object3D::create();
  connector = Connector::create(url, object);
  scene->add(object);
}

void Client::start (){
  assert(scene);

  // Animate callback
  window->animate( [&]( float dt ) -> bool {
    return tick(dt);
  });
}

bool Client::tick(float dt) {
  camera->position().set(5, 1.5, 10);
  // camera->lookAt( scene->position() );

  renderer->render( *scene, *camera );

  return true;
}

void Client::createScene(){
  // Scene
  scene = three::Scene::create();

  // Camera
  camera = three::PerspectiveCamera::create(75, (float) renderer->width() / renderer->height(), .1f, 1000.f);
  scene->add( camera );

  // Lights
  auto pointLight = three::PointLight::create( 0xFFFFFF );
  pointLight->position() = three::Vector3( 0.75, 1, 0.5 ).multiplyScalar(50);
  pointLight->lookAt(three::Vector3(0, 0, 0));
  scene->add( pointLight );

  // Ground plane
  auto material = MeshLambertMaterial::create(
    Material::Parameters().add( "color", Color( 0xffffff ) )
  );

  auto geometry = PlaneGeometry::create( 64, 64 );

  auto plane = Mesh::create( geometry, material );
  plane->rotation().x = -M_PI / 2;
  scene->add( plane );

}

}