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
};
#endif  // RECHARGE_STATION_H
