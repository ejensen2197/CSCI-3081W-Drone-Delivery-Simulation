#include "IPublisher.h"

void IPublisher::addObserver(const IObserver* o) { observers.insert(o); }

void IPublisher::removeObserver(const IObserver* o) { observers.erase(o); }

void IPublisher::notifyObservers(const std::string& message) const {
  for (auto& o : observers) o->notify(message);
}

void IPublisher::addDropoffObserver(IObserver* o) { dropoffObservers.insert(o); }

void IPublisher::notifyDropoff(Vector3 coords) {
  for (auto& o : dropoffObservers) {
    o->notifyDelivery(coords);
  } 
}

void IPublisher::notifyArrival(std::string& type) {
  for (auto& o : dropoffObservers) {
    std::cout << o << std::endl;
    o->notifyArrive(type);
  }
  
}
