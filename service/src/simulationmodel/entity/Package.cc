#include "Package.h"
#include "SimulationModel.h"
#include "Robot.h"

Package::Package(const JsonObject& obj) : IEntity(obj) {}

Vector3 Package::getDestination() const { return destination; }

std::string Package::getStrategyName() const { return strategyName; }

Robot* Package::getOwner() const { return owner; }

bool Package::requiresDelivery() const { return requiresDelivery_; }

void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

void Package::update(double dt) {
  // check if package has arrived, if so try to check if entity has reached the package
  if(this->getArrived()) {
    IEntity* nearest = model->checkArrival(this->getOwner()->getPackageLocation(), this->getOwner());
    if(nearest) { // check that it is not null
      JsonObject det = nearest->getDetails();
      std::string type = det["type"];
      if (type == "thief") {
        this->notifyEntitys(type); 
        std::cout << "Package stolen" << std::endl;
        this->setArrived(false);
      } else if (type == "robot") {
        this->notifyEntitys(type);
        std::cout << "Robot recieved" << std::endl;
        this->setArrived(false);
        handOff();
      }
    }
  }
}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery_ = false;
  std::cout << "Package Dest: " << owner->getPackageLocation() << std::endl;
  destination = owner->getPackageLocation();
}

void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}

void Package::notifyEntitys(std::string type) {
  this->notifyArrival(type);
}

void Package::setArrived(bool val) {
  arrived = val;
}

bool Package::getArrived() {
  return arrived;
}

void Package::dropOff() {
  this->setArrived(true);
  std::cout << "This position: " << this->position << std::endl;
  std::cout << "Destination position: " << this->destination << std::endl;
  notifyDropoff(this->getOwner()->getPackageLocation());
}
