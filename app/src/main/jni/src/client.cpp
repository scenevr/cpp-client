#include "client.h"

#include <three/lights/point_light.h>
#include <three/extras/geometries/plane_geometry.h>
#include <three/objects/mesh.h>
#include <three/materials/mesh_lambert_material.h>
#include <three/core/object3d.h>
#include <three/extras/image_utils.h>
#include <cassert>

namespace scenevr {

using namespace three;
using namespace std;

unsigned char grid_png[] = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10,
  0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x91, 0x68, 0x36, 0x00, 0x00, 0x00,
  0x19, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72,
  0x65, 0x00, 0x41, 0x64, 0x6f, 0x62, 0x65, 0x20, 0x49, 0x6d, 0x61, 0x67,
  0x65, 0x52, 0x65, 0x61, 0x64, 0x79, 0x71, 0xc9, 0x65, 0x3c, 0x00, 0x00,
  0x00, 0x24, 0x49, 0x44, 0x41, 0x54, 0x78, 0xda, 0x62, 0xdc, 0xbb, 0x77,
  0x2f, 0x03, 0x29, 0x80, 0x05, 0x88, 0x9d, 0x9c, 0x9c, 0x88, 0xd7, 0xc0,
  0xc4, 0x40, 0x22, 0x18, 0xd5, 0x30, 0xaa, 0x61, 0xc0, 0x34, 0x00, 0x04,
  0x18, 0x00, 0x32, 0xf3, 0x03, 0x1f, 0x70, 0xc9, 0x5c, 0x8d, 0x00, 0x00,
  0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};
unsigned int grid_png_len = 130;

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
  auto texture = ImageUtils::loadTextureFromMemory(grid_png, grid_png_len);
  texture->wrapS = texture->wrapT = THREE::RepeatWrapping;
  texture->repeat.set(64, 64);

  auto material = MeshLambertMaterial::create(
    Material::Parameters()
      .add("map", texture)
      .add("color", 0xFFFFFF)
  );

  auto geometry = PlaneGeometry::create(64, 64);

  auto plane = Mesh::create( geometry, material );
  plane->rotation().x = -M_PI / 2;
  scene->add( plane );

}

}