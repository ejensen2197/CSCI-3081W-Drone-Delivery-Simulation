#include "Robot.h"
#include "BeelineStrategy.h"

Robot::Robot(const JsonObject& obj) : IEntity(obj) {}

// void Robot::notify(const std::string &message) const {}

void Robot::notifyDelivery(Vector3 packageCoords) {
    std::cout<<"Delivery!!!!!: " <<packageCoords <<std::endl;
    packageCoords.y = 270;
    toPackage = new BeelineStrategy(this->position, packageCoords);
}

void Robot::update(double dt) {
    //check if target package exists 
    if (toPackage && !stolen) {
        toPackage->move(this, dt);

        if (toPackage->isCompleted()) {
            delete toPackage;
            toPackage = nullptr;
        } 
    }

    
    //then check if target package exists, if it does and toPackage->completed then call receive and then pacakge notify it was recieved
    //if it does not exist delete toPackag
    
}

void Robot::notifyArrive(std::string& message) {
    if (message == "human") {
        stolen = true;
        if (toPackage) {
            delete toPackage;
            toPackage = nullptr;
        }
    }
}

void Robot::setPackageLocation(Vector3 location) {
    this->packageLocation = location;
}

Vector3 Robot::getPackageLocation() {
    return packageLocation;
}

void Robot::receive(Package* p) { package = p; } //check if package is stolen if false then set delivered to true 
