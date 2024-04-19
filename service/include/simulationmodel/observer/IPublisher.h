#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

class IPublisher {
 public:
  void addObserver(const IObserver* o);
  void removeObserver(const IObserver* o);
  void notifyObservers(const std::string& message) const;
  void addDropoffObserver(const IObserver* o);
  void notifyDropoff( Vector3 coords) const;

 private:
  std::set<const IObserver*> observers;
  std::set<const IObserver*> dropoffObservers;
};

#endif  // IPUBLISHER_H_
