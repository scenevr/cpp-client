#include "client.h"

#include <three/lights/point_light.h>
#include <three/extras/geometries/plane_geometry.h>
#include <three/objects/mesh.h>
#include <three/materials/mesh_lambert_material.h>
#include <three/core/object3d.h>
#include <three/extras/image_utils.h>
#include <cassert>

#include "assets/grid_image.h"

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

  const auto WALKING_SPEED = 4.0;

  window->addEventListener(SDL_JOYAXISMOTION, [&]( const SDL_Event& event ) {
    if (event.jaxis.axis == 0){
      motion.x = event.jaxis.value * 4.0 / 32768.0;
    }
    if (event.jaxis.axis == 1){
      motion.z = event.jaxis.value * 4.0 / 32768.0;
    }
  });

  window->addEventListener(SDL_JOYBUTTONDOWN, [&]( const SDL_Event& event ) {
    if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
      motion.z = -WALKING_SPEED;
    }
  });

  window->addEventListener(SDL_JOYBUTTONUP, [&]( const SDL_Event& event ) {
    if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
      motion.z = 0;
    }
  });

  window->addEventListener(SDL_FINGERDOWN, [&]( const SDL_Event& event ) {
    motion.z = -WALKING_SPEED;
  });

  window->addEventListener(SDL_FINGERUP, [&]( const SDL_Event& event ) {
    motion.set(0,0,0);
  });

  window->animate( [&]( float dt ) -> bool {
    return tick(dt);
  });
}

bool Client::tick(float dt) {
  stats.update(dt);

  Vector3 v(motion);
  v.multiplyScalar(dt);
  camera->position().add(v);

  // camera->lookAt( scene->position() );

  renderer->render( *scene, *camera );

  return true;
}

void Client::createScene(){
  // Scene
  scene = three::Scene::create();

  // Camera
  camera = three::PerspectiveCamera::create(75, (float) renderer->width() / renderer->height(), .1f, 1000.f);
  camera->position().set(5, 1.5, 10);
  scene->add( camera );

  // Lights
  auto pointLight = three::PointLight::create( 0xFFFFFF );
  pointLight->position() = three::Vector3( 0.75, 1, 0.5 ).multiplyScalar(50);
  pointLight->lookAt(three::Vector3(0, 0, 0));
  scene->add( pointLight );

  // Ground plane
  auto texture = ImageUtils::loadTextureFromMemory(images_grid_png, images_grid_png_len);
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