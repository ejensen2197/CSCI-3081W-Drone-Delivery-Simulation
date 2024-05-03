#ifndef BATTERY_H_
#define BATTERY_H_

#include "Drone.h"
#include "PathStrategy.h"
#include "IEntityDecorator.h"
#include "IStrategy.h"
#include "BeelineStrategy.h"

/**
 * @class BatteryDecorator
 * @brief Adds a battery on to the drone. The battery decrements 
 * based on how much distance the drone travels. 
 */
class BatteryDecorator : public IEntityDecorator<Drone> {
 public:
  /**
   * @brief Sets battery level and assigns drone pointer with current drone
   * @param d Drone* pointer containing the drone to have the battery
   */
  BatteryDecorator(Drone* d);

  /**
   * @brief Destructor
   */
  ~BatteryDecorator();

  /**
   * @brief Updates the drone's battery based its distance travelled
   * @param dt Delta time
   */
  void update(double dt);

  /**
   * @brief Returns true if drone is dead
   */
  bool isDead();

  /**
   * @brief Returns battery of drone
   */
  double getBatteryLevel();

  /**
   * @brief Checks if drone can make delivery
   * @param dt Delta Time
   */
  bool canMakeTrip(double dt);

  /**
   * @brief Finds the nearest recharge stations and 
   * sets a strategy to it
   * @param dt Delta Time
   */
  void findRecharge(double dt);

  /**
   * @brief Returns trip distance
   */
  double calcDist();

 private:
  Drone* drone = nullptr;
  float batteryLevel = 100;
  float maxCapacity = 100;
  bool atRecharge = false;
  bool onDelivery = false;
  IStrategy* rechargeStrategy = nullptr;
  Vector3 lastPosition;
  bool needCheck = true;
  bool approved = false;
};
#endif  // BATTERY_DECORATOR_H_
