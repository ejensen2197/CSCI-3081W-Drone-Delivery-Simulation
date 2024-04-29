#ifndef THIEF_H_
#define THIEF_H_

#include "IEntity.h"
#include "IStrategy.h"
#include "Human.h"

class Thief;

class Thief : public Human {
 public:
  /**
   * @brief Thief constructor
   * @param obj JSON object containing the thief's information
   */
  Thief(const JsonObject& obj);

  /**
   * @brief Thief destructor
   */
  ~Thief();

  /**
   * @brief Thief constructor
   * @param obj JSON object containing the thief's information
   */
  void update(double dt);

  /**
   * @brief Changes the thief's color
   */
  std::string getColor() const;

  /**
   * @brief Notifies thief of a package delivery if
   * thief is within a specific distance from package
   * 
   * @param packageCoords Type Vector3 contains coordinates
   * of package that was delivered
  */
  void notifyDelivery(Vector3 packageCoords);

  /**
   * @brief Notifies thief of an entity arrival to package 
   * 
   * @param message Type string address contains entity type
   * that reaches the package first
  */
  void notifyArrive(std::string& message);

  /**
   * @brief will stop stealing package if 
   * robot picks it up
  */
  void cancelSteal();

  /**
   * @brief Thief steals package 
  */
  void steal();

 private:
  static Vector3 kellerPosition;
  IStrategy* movement = nullptr;
  bool atKeller = false;
  bool stealPackage = false;
  Vector3 targetPackage;
};

#endif // THIEF_H_
