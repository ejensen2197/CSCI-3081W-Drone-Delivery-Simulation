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

  /**
   * @brief Adds observer who subscribes to package 
   * 
   * @param o Type IObserver pointer contains observer
   * who subscribes to package
  */
  virtual void addDropoffObserver(IObserver* o);

  /**
   * @brief Notifies observers of a package delivery 
   * 
   * @param coords Type Vector3 contains coordinates
   * of package that was delivered
  */
  virtual void notifyDropoff(Vector3 coords);

  /**
   * @brief Notifies observers of entity arrival to
   * package 
   * 
   * @param type Type string address contains type
   * entity that arrived to package
  */
  virtual void notifyArrival(std::string& type, int id);

 private:
  std::set<const IObserver*> observers;
  std::set<IObserver*> dropoffObservers;
};

#endif  // IPUBLISHER_H_
