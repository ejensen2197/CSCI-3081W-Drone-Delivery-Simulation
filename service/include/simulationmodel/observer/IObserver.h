#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>
#include <vector>
#include "vector3.h"
class IObserver {
 public:
  virtual void notify(const std::string &message) const = 0;

  /**
   * @brief Notifies observer of a package delivery 
   * 
   * @param packageCoords Type Vector3 contains coordinates
   * of package that was delivered
  */
  virtual void notifyDelivery(Vector3 packageCoords) {}

  /**
   * @brief Notifies observer of an entity arrival to package 
   * 
   * @param type Type string address contains entity type
   * that reaches the package first
   * @param id Type int of id of IEntity
  */
  virtual void notifyArrive(std::string &type, int id) {}

  /**
   * @brief Sets id attribute
   * 
   * @param id_ Type int containing id
  */
  virtual void setID(int id_) { id = id_; }

  /**
   * @brief Returns id 
  */
  virtual int getID() { return id; }

 private:
  int id = 0;
};

#endif  // IOBSERVER_H_
