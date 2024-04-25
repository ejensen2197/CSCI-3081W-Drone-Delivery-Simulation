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
  void addDropoffObserver(IObserver* o);
  void notifyDropoff(Vector3 coords);
  void notifyArrival(std::string& message);

 private:
  std::set<const IObserver*> observers;
  std::set<IObserver*> dropoffObservers;
};

#endif  // IPUBLISHER_H_
