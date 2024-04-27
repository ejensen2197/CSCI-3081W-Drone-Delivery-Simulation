#ifndef THIEF_H_
#define THIEF_H_

#include <vector>

#include "IEntityFactory.h"
#include "Thief.h"

/**
    *@brief Thief Factory to produce Thief class.
    *   
*/
class ThiefFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for HumanFactory class.
   **/
  virtual ~ThiefFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif
