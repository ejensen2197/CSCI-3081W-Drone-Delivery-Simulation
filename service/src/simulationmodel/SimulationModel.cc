#include "SimulationModel.h"

#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "PackageFactory.h"
#include "RobotFactory.h"
#include "RechargeStationFactory.h"


SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.addFactory(new DroneFactory());
  entityFactory.addFactory(new PackageFactory());
  entityFactory.addFactory(new RobotFactory());
  entityFactory.addFactory(new HumanFactory());
  entityFactory.addFactory(new HelicopterFactory());
  entityFactory.addFactory(new RechargeStationFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

IEntity* SimulationModel::createEntity(const JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;
  
  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.createEntity(entity)) {
    // Call AddEntity to add it to the view
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
    // Add the simulation model as a observer to myNewEntity
    myNewEntity->addObserver(this);
  }
  std::string type = entity["type"];
  if (type == "Recharge") {
    station.push_back(myNewEntity->getPosition());
  }

  if (type == "human") {
    humans.push_back(myNewEntity);
  }

  return myNewEntity;
}

Vector3 SimulationModel::nearestRecharge(Vector3 pos) {
  Vector3 closest = station[0];
  double distance = pos.dist(station[0]);
  for (int i =0; i< station.size(); i++)
  {
    if (distance < (station[i] - pos).magnitude())
    {
      distance = (station[i] - pos).magnitude();
      closest = station[i];
    }
  }
  return closest;
}

void SimulationModel::removeEntity(int id) { removed.insert(id); }

/// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(const JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  Package* package = nullptr;

  for (auto& [id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery()) {
          package = p;
          break;
        }
      }
    }
  }

  // why is there something in the set initially at this point despite the only adding observers after the if
  if (receiver && package) {
    package->addDropoffObserver(receiver);
    for(int i = 0; i < humans.size(); i++) {
      // add all currently existing humans to list of observers
      package->addDropoffObserver(humans[i]);
    }
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

const routing::Graph* SimulationModel::getGraph() const { return graph; }

void SimulationModel::setGraph(const routing::Graph* graph) {
  if (this->graph) delete this->graph;
  this->graph = graph;
}

/// Updates the simulation
void SimulationModel::update(double dt) {
  for (auto& [id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

void SimulationModel::stop(void) {}

void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

void SimulationModel::notify(const std::string& message) const {
  JsonObject details;
  details["message"] = message;
  this->controller.sendEventToView("Notification", details);
}

IEntity* SimulationModel::checkArrival(Vector3 package, IEntity* robot) {
  if (humans.size() != 0) {
    IEntity* closest = humans[0];
    double dist = 0;
    for (int i = 0; i < humans.size(); i++) {
      if (dist < humans[i]->getPosition().dist(closest->getPosition())) {
        dist = humans[i]->getPosition().dist(closest->getPosition());
        closest = humans[i];
      }
    }
    // check if the robot is closer than the closest human
    if (closest->getPosition().dist(robot->getPosition()) < dist) {
      closest = robot;
    }
    // only return something if it is within a specific threshold
    if (closest->getPosition().dist(package) < 1.0) {
      return closest;
    }
  }
  //else return nullptr
  return nullptr;
}
