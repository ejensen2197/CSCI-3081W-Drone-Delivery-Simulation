#include "RechargeStationFactory.h"

IEntity* RechargeStationFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("Recharge") == 0) {
    std::cout << "Recharge Station Created" << std::endl;
    return new RechargeStation(entity);
  }
  return nullptr;
}
