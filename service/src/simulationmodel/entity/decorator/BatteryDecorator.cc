#include "BatteryDecorator.h"
#include "SimulationModel.h"

BatteryDecorator::BatteryDecorator(Drone* d) : IEntityDecorator(d) {
    this->batteryLevel = 200;
    this->maxCapacity = 200;
    this->lastPosition = sub->getPosition();
}

BatteryDecorator::~BatteryDecorator() {
    delete this->drone;
}

void BatteryDecorator::update(double dt) {
    // if at the recharge it should stay there and recharge until at full
    if (atRecharge) {
        if (batteryLevel > maxCapacity) {
            atRecharge = false;
            needCheck = true;
        } else {
            batteryLevel += 10*dt;
            std::cout << "battery Level: " << batteryLevel << std::endl;
        }
    } else if (batteryLevel < 0) {
        // do nothing because it is dead
    } else if (batteryLevel != 0 && sub->isAvailable()) {
        // idle
        needCheck = true;
        sub->update(dt);
    } else if (canMakeTrip(dt) && sub->isAvailable() == false) {
        // if it can make the delivery without dying
        needCheck = false;
        sub->update(dt);
        double diff = this->lastPosition.dist(sub->getPosition());
        this->batteryLevel = batteryLevel - (diff/60);
        this->lastPosition = sub->getPosition();
    } else if ((!canMakeTrip(dt) &&
                sub->isAvailable() == false) ||
                batteryLevel < 20) {
        // case for needing to recharge
        findRecharge(dt);
    }
}

double BatteryDecorator::getBatteryLevel() {
    return batteryLevel;
}

double BatteryDecorator::calcDist() {
    double totalDist = 0;
    if (sub->getPackageStrat()) {
        // get package strategy
        IStrategy* packageStrat = sub->getPackageStrat();
        totalDist += packageStrat->dist();
    }

    if (sub->getFinalDestStrat()) {
        // get final destination strategy
        IStrategy* finalDestStrat = sub->getFinalDestStrat();
        totalDist += finalDestStrat->dist();
    }
    return totalDist;
}

// package location speed and distance tells how long
bool BatteryDecorator::canMakeTrip(double dt) {
    if (needCheck) {
        // gets how much battery path will take
        double pathBattery = calcDist();
        // distance we can travel
        double calcPosDistance = batteryLevel*50;
        double threshhold = 10;
        // calculates min distance to recharge station with this
        if (pathBattery + (threshhold * 60) < calcPosDistance) {
            approved = true;
            std::cout << "Can make trip total battery need is: "
            << pathBattery +(threshhold * 60)
            << " total path battery of drone: "
            << calcPosDistance << std::endl;
            return approved;
        }
        // std::cout << "Cannot make trip" << std::endl;
        approved = false;
        return approved;
    }
    return approved;
}

bool BatteryDecorator::isDead() {
    if (batteryLevel == 0) {
        return true;
    }
    return false;
}

void BatteryDecorator::findRecharge(double dt) {
    if (model) {
        // logic to get nearest recharge station
        Vector3 nearestRecharge = model->nearestRecharge(sub->getPosition());
        nearestRecharge.y = sub->getPosition().y;
        // std::cout << "nearest Recharge: " << nearestRecharge << std::endl;
        if (rechargeStrategy == nullptr) {
            // strategy to nearest recharge station
            rechargeStrategy = new BeelineStrategy(sub->getPosition(),
                                    nearestRecharge);
        }
        rechargeStrategy->move(sub, dt);  // move drone to recharge station
        double diff = this->lastPosition.dist(sub->getPosition());
        this->batteryLevel = batteryLevel - (diff/100);
        this->lastPosition = sub->getPosition();
        // checking that the drone arrived to recharge station
        if ((sub->getPosition() - nearestRecharge).magnitude() < 1.0 ||
        rechargeStrategy->isCompleted()) {
            // set to true so the update function knows to charge drone
            atRecharge = true;
            delete rechargeStrategy;
            rechargeStrategy = nullptr;
            if (sub->isAvailable() == false) {
               sub->setPackageStrat();  // calling new package creation
            }
        }
    }
}
