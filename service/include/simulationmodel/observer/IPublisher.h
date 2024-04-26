#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

class IPublisher {
 public:
  virtual void addObserver(const IObserver* o);
  virtual void removeObserver(const IObserver* o);
  virtual void notifyObservers(const std::string& message) const;
  virtual void addDropoffObserver(IObserver* o);
  virtual void notifyDropoff(Vector3 coords);
  virtual void notifyArrival(std::string& message);

 private:
  std::set<const IObserver*> observers;
  std::set<IObserver*> dropoffObservers;
};

#endif  // IPUBLISHER_H_
