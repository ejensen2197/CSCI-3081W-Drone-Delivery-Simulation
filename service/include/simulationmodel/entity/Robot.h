#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"
#include "IStrategy.h"

class Package;

/**
 * @class Robot
 * @brief Represents a robot in a physical system
 *
 * Robots move using euler integration based on a specified
 * velocity and direction.
 */
class Robot : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the robot's information
   */
  Robot(const JsonObject& obj);

  /**
   * @brief Updates the Package
   *
   * @param dt difference in time since last update
   */
  void update(double dt);

  /**
   * @brief Receives the passed in package
   *
   * @param Package* Package to be received by the robot
   */
  void receive(Package* p);

  // void notify(const std::string &message) const;

  void notifyDelivery(Vector3 packageCoords);

  void notifyArrive(std::string &message);

  void setPackageLocation(Vector3 location);

  Vector3 getPackageLocation();

  bool requestedDelivery = true;

 protected:
  bool delivered = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  bool stolen = false;
  Vector3 packageLocation;
};

#endif  // ROBOT_H
