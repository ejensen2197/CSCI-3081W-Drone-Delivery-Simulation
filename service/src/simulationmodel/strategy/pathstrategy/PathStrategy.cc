#include "PathStrategy.h"

PathStrategy::PathStrategy(std::vector<Vector3> p) : path(p), index(0) {}

std::vector<Vector3> PathStrategy::getPoints() {
  return path;
}

double PathStrategy::dist() {
  double totalDist = 0;
  for(int i = 0; i < path.size()-1; i++) {
    totalDist += (path[i] - path[i+1]).magnitude();
  }
  return totalDist;
}

void PathStrategy::move(IEntity* entity, double dt) {
  if (isCompleted()) return;

  Vector3 vi = path[index];
  Vector3 dir = (vi - entity->getPosition()).unit();

  entity->setPosition(entity->getPosition() + dir * entity->getSpeed() * dt);
  entity->setDirection(dir);

  if (entity->getPosition().dist(vi) < 4) index++;
}

bool PathStrategy::isCompleted() { return index >= path.size(); }
