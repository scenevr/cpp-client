#include "client.h"

#include <three/lights/point_light.h>
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
}

void Client::start (){
  assert(scene);

  // Animate callback
  window->animate( [&]( float dt ) -> bool {
    return tick(dt);
  });
}

bool Client::tick(float dt) {
  camera->position().set(0, 5, -10);
  camera->lookAt( scene->position() );

  renderer->render( *scene, *camera );

  return true;
}

void Client::createScene(){
  // Scene
  scene = three::Scene::create();

  // Camera
  camera = three::PerspectiveCamera::create(50, (float) renderer->width() / renderer->height(), .1f, 1000.f);
  scene->add( camera );

  // Lights
  auto pointLight = three::PointLight::create( 0xFFFFFF );
  pointLight->position() = three::Vector3( 0.75, 1, 0.5 ).multiplyScalar(50);
  pointLight->lookAt(three::Vector3(0, 0, 0));
  scene->add( pointLight );
}

}