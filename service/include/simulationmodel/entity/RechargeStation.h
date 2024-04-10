#ifndef RECHARGE_STATION_H
#define RECHARGE_STATION_H

#include <vector>
#include "Drone.h"

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

class RechargeStation;

class RechargeStation : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the recharge station's information
   */
  RechargeStation(const JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~RechargeStation();

  void update(double dt);

  /**
   * @brief Charges the battery of the drone
   * @param dt distance traveled
   */
    // void chargeBattery(double dt);

    /**
     * @brief Adds a drone to the recharge station
     * @param drone drone to be added
     */

    virtual void addDrone(Drone* drone);

    /**
     * @brief Removes a drone from the recharge station
     * @param drone drone to be removed
     */
    virtual void removeDrone(Drone* drone);

    /**
     * @brief Returns the maximum capacity of the recharge station
     * @return maximum capacity of the recharge station
     */

    double reacherMaxCapacity();
    protected:
    std::vector<Drone*> droneQue;
    double maxCapacity = 10;
};

#endif // RECHARGE_STATION_H