#include "DroneFactory.h"
#include "BatteryDecorator.h"

IEntity* DroneFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;
    return new BatteryDecorator(new Drone(entity));
  }
  return nullptr;
}
