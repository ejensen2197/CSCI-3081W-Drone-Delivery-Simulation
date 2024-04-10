#include "RechargeStation.h"

RechargeStation::RechargeStation(const JsonObject& obj) : IEntity(obj) {}

RechargeStation::~RechargeStation() {}

// void RechargeStation::chargeBattery(double dt) {
//   for (auto drone : droneQue) {
//     drone->chargeBattery(dt);
//   }
// }

// void RechargeStation::addDrone(Drone* drone) {
//   if (droneQue.size() < maxCapacity) {
//     droneQue.push_back(drone);
//   }
// }

// void RechargeStation::removeDrone(Drone* drone) {
//   for (auto it = droneQue.begin(); it != droneQue.end(); ++it) {
//     if (*it == drone) {
//       droneQue.erase(it);
//       break;
//     }
//   }
// }

double RechargeStation::reacherMaxCapacity() { return maxCapacity; 
}
