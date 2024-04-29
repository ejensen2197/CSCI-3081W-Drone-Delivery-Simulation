#define _USE_MATH_DEFINES
#include "Thief.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "SimulationModel.h"
#include "BeelineStrategy.h"

Vector3 Thief::kellerPosition(64.0, 254.0, -210.0);

Thief::Thief(const JsonObject& obj) : Human(obj) {
}

Thief::~Thief() {
  if (movement) delete movement;
}

std::string Thief::getColor() const {
  auto format = "hsl(%lf, %lf%%, %lf%%)";
  char color[100];
  snprintf(color, sizeof(color), format, 0, 100, 50);
  return color;
}

void Thief::update(double dt) {
  if (movement && !movement->isCompleted()) {
    movement->move(this, dt);
    bool nearKeller = this->position.dist(Thief::kellerPosition) < 85;
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

void Thief::notifyDelivery(Vector3 packageCoords) {
  if(this->position.dist(packageCoords) > 50 && !stealPackage){
    packageCoords.y = 270;
    targetPackage = packageCoords;
    if(movement) delete movement;
    std::cout <<"I want Package" << std::endl;
    movement = new BeelineStrategy(this->position, packageCoords);
    stealPackage = true;
  }
}

void Thief::cancelSteal() {
  stealPackage = false;
  if(movement) delete movement;
  Vector3 dest;
  dest.x = ((static_cast<double>(rand())) / RAND_MAX) * (2900) - 1400;
  dest.y = position.y;
  dest.z = ((static_cast<double>(rand())) / RAND_MAX) * (1600) - 800;
  if (model) movement = new AstarStrategy(position, dest, model->getGraph());
}

void Thief::steal() {
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

void Thief::notifyArrive(std::string &message) {
  if (message == "thief") {
    steal();
  } else if (message == "robot") {
    std::cout <<message << std::endl;
    cancelSteal();
  }
}