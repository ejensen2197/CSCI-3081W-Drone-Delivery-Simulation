#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include <deque>
#include <map>
#include <set>

#include "CompositeFactory.h"
#include "Drone.h"
#include "IController.h"
#include "IEntity.h"
#include "IObserver.h"
#include "Robot.h"
#include "Graph.h"
#include "RechargeStation.h"

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel : public IObserver {
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type Graph* contain the new graph for SimulationModel
   **/
  void setGraph(const routing::Graph* graph);

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   *which entity to create
   **/
  IEntity* createEntity(const JsonObject& entity);

  /**
   * @brief Removes entity with given ID from the simulation
   *
   * @param id of the entity to be removed
   */
  void removeEntity(int id);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   *the detail of the trip being scheduled
   **/
  void scheduleTrip(const JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  /**
   * @brief Stops the simulation
   * @return Void
   **/
  void stop();

  /**
   * @brief Returns the graph of the map
   *
   * @returns Graph* graph pointer
   */
  const routing::Graph* getGraph() const;

  void notify(const std::string& message) const;

  std::deque<Package*> scheduledDeliveries;
  /**
   * @brief gets the closest recharge station from position
   * @param pos type Vector3, the initial position
   *
   * @returns the location of nearest recharge station
   */
  Vector3 nearestRecharge(Vector3 pos);
  /**
   * @brief gets closest package at position
   * @param currentPosition type Vector3 current position
   *
   * @returns the position of closest package
   */
  Vector3 getClosestPackage(const Vector3& currentPosition);
 protected:
  IController& controller;
  std::map<int, IEntity*> entities;
  std::set<int> removed;
  void removeFromSim(int id);
  const routing::Graph* graph = nullptr;
  CompositeFactory entityFactory;
  std::vector <Vector3> station;
};

#endif
