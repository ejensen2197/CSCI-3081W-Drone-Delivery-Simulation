#ifndef PACKAGE_H
#define PACKAGE_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"


class Robot;

class Package : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the package's information
   */
  Package(const JsonObject& obj);

  /**
   * @brief Gets the Package's destination
   * @return The Package's destination
   */
  virtual Vector3 getDestination() const;

  /**
   * @brief Returns the name of the strategy for this package
   *
   * @returns String name of strategy
   */
  virtual std::string getStrategyName() const;

  /**
   * @brief Returns the owner of the package
   *
   * @return pointer to Robot owning the package
   */
  virtual Robot* getOwner() const;

  /**
   * @brief Returns whether or not the package needs to be delivered
   *
   * @return boolean value of the above statement
   */
  virtual bool requiresDelivery() const;

  /**
   * @brief Set the Strategy Name
   *
   * @param strategyName_ Strategy name
   */
  virtual void setStrategyName(std::string strategyName_);

  /**
   * @brief Updates the Package by checking for nearest entity
   *
   * @param dt difference in time since last update
   */
  virtual void update(double dt);

  /**
   * @brief Sets the attributes for delivery
   *
   * @param owner Robot for the package to be delivered to
   */
  virtual void initDelivery(Robot* owner);

  /**
   * @brief Hands the package off to the owner
   */
  virtual void handOff();

  /**
   * @brief notifies observers of delivery
   */
  virtual void dropOff();

  /**
   * @brief getter for arrived variable 
   */
  virtual bool getArrived();

  /**
   * @brief setter for arrived variable
   * 
   * @param val Type bool contains what to set arrived
   */
  virtual void setArrived(bool val);

  /**
   * @brief notify observers if entity arrives at package
   * 
   * @param type Type string of type entity at package
   * @param id Type int of id of entity at package
   */
  virtual void notifyEntitys(std::string type, int id);

 protected:
  bool requiresDelivery_ = true;
  Vector3 destination;
  std::string strategyName;
  Robot* owner = nullptr;
  bool arrived = false;
};

#endif  // PACKAGE_H
