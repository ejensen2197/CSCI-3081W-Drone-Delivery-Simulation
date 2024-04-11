#ifndef BATTERY_H_
#define BATTERY_H_

#include "Drone.h"
#include "IEntityDecorator.h"

class BatteryDecorator : public IEntityDecorator<Drone> {
 public:
  BatteryDecorator(Drone* d);
  ~BatteryDecorator();
  void update(double dt);
  bool isFull();
  void charge(double dt);
  bool isDead();
  double getBatteryLevel();

 private:
  Drone* drone = nullptr;
  float batteryLevel = 100;
  float maxCapacity = 100;
  bool isCharging = false;

};

#endif