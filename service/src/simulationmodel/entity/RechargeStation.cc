#include "RechargeStation.h"

RechargeStation::RechargeStation(const JsonObject& obj) : IEntity(obj) {}

RechargeStation::~RechargeStation() {}

// void RechargeStation::chargeBattery(double dt) {
//   for (auto drone : droneQue) {
//     drone->chargeBattery(dt);
//   }
// }
void RechargeStation::update(double dt) {}

void RechargeStation::addDrone(Drone* drone) {
  if (droneQue.size() < maxCapacity) {
    droneQue.push_back(drone);
  }
}

void RechargeStation::removeDrone(Drone* drone) {
    for (int i = 0; i < droneQue.size(); i++) {
        if (droneQue[i] == drone) {
            droneQue.erase(droneQue.begin() + i);
            break;
        }
    }
}

double RechargeStation::reacherMaxCapacity() { return maxCapacity; 
}
