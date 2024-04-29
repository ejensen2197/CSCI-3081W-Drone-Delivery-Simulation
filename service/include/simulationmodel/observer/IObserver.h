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
   * @param message Type string address contains entity type
   * that reaches the package first
  */
  virtual void notifyArrive(std::string &message) {}
};

#endif  // IOBSERVER_H_
