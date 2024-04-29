#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"
#include "BeelineStrategy.h"

Vector3 Human::kellerPosition(64.0, 254.0, -210.0);

Human::Human(const JsonObject& obj) : IEntity(obj) {}

Human::~Human() {
  if (movement) delete movement;
}

void Human::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
    bool nearKeller = this->position.dist(Human::kellerPosition) < 85;
    if (nearKeller && !this->atKeller) {
      std::string message = this->getName() + " visited Keller hall";
      notifyObservers(message);
    }
    atKeller = nearKeller;
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
  }
}

void Human::notifyDelivery(Vector3 packageCoords) {
  if(this->position.dist(packageCoords) > 50 && !stealPackage){
    packageCoords.y = 270;
    targetPackage = packageCoords;
    if(movement) delete movement;
    movement = new BeelineStrategy(this->position, packageCoords);
    stealPackage = true;
  }
  // if (!stealPackage) {
  //   stealPackage = true;
  //   targetPackage = packageCoords;
  // }
}

void Human::cancelSteal() {
  stealPackage = false;
  if(movement) delete movement;
  Vector3 dest;
  dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
  dest.y = position.y;
  dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
  if (model) movement = new AstarStrategy(position, dest, model->getGraph());
}

void Human::steal() {
  std::string message = this->getName() + " stole a package";
  notifyObservers(message);
  stealPackage = false;
  if(movement) delete movement;
  Vector3 dest;
  dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
  dest.y = position.y;
  dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
  if (model) movement = new AstarStrategy(position, dest, model->getGraph());
}

void Human::notifyArrive(std::string &message) {
  if (message == "human") {
    steal();
  } else if (message == "robot") {
    std::cout <<message << std::endl;
    cancelSteal();
  }
}