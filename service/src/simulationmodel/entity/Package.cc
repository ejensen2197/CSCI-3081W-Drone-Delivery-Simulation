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
//how do I fix the errors?
// how do I add it all the current humans and potential new humans to the list of observers
// how do I change the location of the robot to be random within a specific parameter?
void Package::update(double dt) {
  // check if package has arrived, if so try to check if entity has reached the package
  if(arrived) {
    IEntity* nearest = model->checkArrival(this->position, this->owner);
    if(nearest) { // check that it is not null
      JsonObject det = nearest->getDetails();
      std::string type = det["type"];
      if (type == "human") {
        notifyArrival(type); 
        std::cout << "Package stolen" << std::endl;
        arrived = false;
      } else if (type == "robot") {
        notifyArrival(type);
        std::cout << "Robot recieved" << std::endl;
        arrived = false;
        handOff();
      }
    }
  }
}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery_ = false;
  std::cout << "Package Dest: " <<owner->getPackageLocation() << std::endl;
  destination = owner->getPackageLocation();
}

void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}

void Package::dropOff() {
  arrived = true;
  std::cout << "This position: " << this->position << std::endl;
  std::cout << "Destination position: " << this->destination << std::endl;
  //why can't I just use owner rather than getOwner()
  notifyDropoff(this->getOwner()->getPackageLocation());
}
