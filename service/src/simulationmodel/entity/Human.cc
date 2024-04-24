#define _USE_MATH_DEFINES
#include "Human.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"

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
  } else if (stealPackage && !movement) {
    //
    if (model) movement = new AstarStrategy(position, targetPackage, model->getGraph());
  } else if (movement && movement->isCompleted() && stealPackage) {
    // human moved to package location and either stole package or did not
    // have a package pointer and check if package exists, if it does then it has been stolen
    // if stolen then notify simulation model to schedule another delivery
    stealPackage = false;
  } else {
    if (movement) delete movement;
    Vector3 dest;
    dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
    dest.y = position.y;
    dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
    if (model) movement = new AstarStrategy(position, dest, model->getGraph());
  }
  // updating distance from package
  if (stealPackage) {
    distanceFromPackage = position.dist(targetPackage);
  }
  else {
    distanceFromPackage = std::numeric_limits<double>::max();
  }
}

void Human::notifyDelivery(Vector3 packageCoords) {
  if (!stealPackage) {
    stealPackage = true;
    targetPackage = packageCoords;
    distanceFromPackage = position.dist(targetPackage);
  }
}