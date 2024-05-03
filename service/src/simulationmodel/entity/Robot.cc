#include "Robot.h"
#include "BeelineStrategy.h"
#include "AstarStrategy.h"
#include "SimulationModel.h"

Robot::Robot(const JsonObject& obj) : IEntity(obj) {}

// void Robot::notify(const std::string &message) const {}

void Robot::notifyDelivery(Vector3 packageCoords) {
    std::cout << "Delivery!!!!!: " << packageCoords << std::endl;
    packageCoords.y = 270;
    this->speed = 20;
    toPackage =  new AstarStrategy(
        this->position, packageCoords, model->getGraph());
}

void Robot::update(double dt) {
    // check if target package exists
    if (toPackage && !stolen) {
        toPackage->move(this, dt);

        if (toPackage->isCompleted()) {
            delete toPackage;
            toPackage = nullptr;
        }
    }
}

void Robot::notifyArrive(std::string& type, int id) {
    if (type == "thief") {
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

void Robot::receive(Package* p) { package = p; }
