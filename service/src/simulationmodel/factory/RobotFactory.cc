#include "RobotFactory.h"

IEntity* RobotFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("robot") == 0) {
    Robot* newRob = new Robot(entity);
    Vector3 origLoc = newRob->getPosition();
    newRob->setPackageLocation(newRob->getPosition());
    
    // Define the radius within which the new position should be generated
    double radius = 600.0; // Adjust this value as needed

    // Generate random offsets within the radius
    double deltaX = ((static_cast<double>(rand())) / RAND_MAX) * (2 * radius) - radius;
    double deltaZ = ((static_cast<double>(rand())) / RAND_MAX) * (2 * radius) - radius;

    // Calculate the new position
    Vector3 dest;
    dest.x = origLoc.x + deltaX;
    dest.y = origLoc.y; // Assuming y-coordinate remains the same
    dest.z = origLoc.z + deltaZ;
    newRob->setPosition(dest);

    std::cout << "Robot Created" << std::endl;
    std::cout << "Original Location" << origLoc << std::endl;
    std::cout << "New Location" << dest << std::endl;
    return newRob;
  }
  return nullptr;
}
