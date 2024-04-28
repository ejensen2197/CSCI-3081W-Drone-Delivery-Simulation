#include "HumanFactory.h"
#include "Thief.h"


IEntity* HumanFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  
  // create a 50/50 rand, if the entity is a thief or a human, if theif call theif factory, else human
  if (rand() % 2 == 0) {
    type = "thief";
    entity["type"] = "thief";
    entity["name"] = "Thief";
    if (type.compare("thief") == 0) {
      std::cout << "Thief Created" << std::endl;
      return new Thief(entity);
    }
  } else {
    if (type.compare("human") == 0) {
      std::cout << "Human Created" << std::endl;
      return new Human(entity);
    }
  }
  return nullptr;
}
