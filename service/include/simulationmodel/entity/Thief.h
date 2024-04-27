#ifndef THIEF_H_
#define THIEF_H_

#include "IEntity.h"
#include "IStrategy.h"

class Thief;

class Thief : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Thief(const JsonObject& obj);

  ~Thief();

  void update(double dt);

  // void notify(const std::string &message) const {};

  void notifyDelivery(Vector3 packageCoords);

  void notifyArrive(std::string& message);

  void cancelSteal();

  void steal();

 private:
  static Vector3 kellerPosition;
  IStrategy* movement = nullptr;
  bool atKeller = false;
  bool stealPackage = false;
  Vector3 targetPackage;
};

#endif // THIEF_H_
