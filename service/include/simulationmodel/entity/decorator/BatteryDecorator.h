#ifndef BATTERY_H_
#define BATTERY_H_

#include "Drone.h"
#include "PathStrategy.h"
#include "IEntityDecorator.h"
#include "IStrategy.h"
#include "BeelineStrategy.h"


class BatteryDecorator : public IEntityDecorator<Drone> {
 public:
  BatteryDecorator(Drone* d);
  ~BatteryDecorator();
  void update(double dt);
  bool isFull(); //could be deletied
  // void charge(double dt);
  bool isDead();
  double getBatteryLevel();
  bool canMakeTrip(double dt);
  void findRecharge(double dt);
  double calcTime(); 

 private:
  Drone* drone = nullptr;
  float batteryLevel = 100;
  float maxCapacity = 100;
  //bool isCharging = false; // could be deleted
  Vector3 rechargeStation1 = {299,49,29};
  bool atRecharge = false;
  bool onDelivery = false;
  IStrategy* rechargeStrategy = nullptr;
  Vector3 lastPosition;

};

#endif