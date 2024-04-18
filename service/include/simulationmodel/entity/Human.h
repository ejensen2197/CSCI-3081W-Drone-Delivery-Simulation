#ifndef HUMAN_H_
#define HUMAN_H_

#include "IEntity.h"
#include "IStrategy.h"

class Human : public IEntity, public IObserver {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Human(const JsonObject& obj);

  ~Human();

  void update(double dt);

  void notify(const std::string &message) {};

 private:
  static Vector3 kellerPosition;
  IStrategy* movement = nullptr;
  bool atKeller = false;
  bool stealPackage = false;
  Vector3 targetPackage;
};

#endif
