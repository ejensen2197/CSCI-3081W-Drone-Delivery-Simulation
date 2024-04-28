#ifndef THIEF_H_
#define THIEF_H_

#include "IEntity.h"
#include "IStrategy.h"
#include "Human.h"

class Thief;

class Thief : public Human {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Thief(const JsonObject& obj);

  ~Thief();

  void update(double dt);

  std::string getColor() const;

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
