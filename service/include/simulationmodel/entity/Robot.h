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
   * @brief Constructs a new robot object
   * @param obj JSON object containing the robot's information
   */
  Robot(const JsonObject& obj);

  /**
   * @brief Updates the Package state and position
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
  /**
   * @brief notifies the robot of a package delivery, initializing movement towards it
   *
   * @param packageCoords coordinates of the delivered package
   */
  void notifyDelivery(Vector3 packageCoords);

  /**
   * @brief package arrival at the destination
   *
   * @param type Type String of type of entity
   * @param id ID of Entity
   */
  void notifyArrive(std::string &type, int id);

  /**
   * @brief sets the location of the target package
   *
   * @param location the coordinates where the package is located
   */
  void setPackageLocation(Vector3 location);

  /**
   * @brief gets the location of the package associated with robot
   *
   * @return the current package location as a Vector3 object
   */
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
