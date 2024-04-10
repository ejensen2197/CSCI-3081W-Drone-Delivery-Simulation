#ifndef RechageStation_FACTORY_H_
#define RechageStation_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "RechargeStation.h"

/**
 * @brief Factory for creating RechargeStation objects.
 **/
class RechargeStationFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for RechargeStationFactory class.
   **/
  virtual ~RechargeStationFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif