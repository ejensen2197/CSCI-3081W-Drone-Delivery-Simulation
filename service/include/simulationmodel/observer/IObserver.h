#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>
#include <vector>
#include "vector3.h"
class IObserver {
 public:
  virtual void notify(const std::string &message) const = 0;

  virtual void notifyDelivery(Vector3 packageCoords) {}

  virtual void notifyArrive(std::string &message) {}
};

#endif  // IOBSERVER_H_
