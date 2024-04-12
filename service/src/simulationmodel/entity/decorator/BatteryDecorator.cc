#include "BatteryDecorator.h"

BatteryDecorator::BatteryDecorator(Drone* d) : IEntityDecorator(d) {
    batteryLevel = 100;
    maxCapacity = 100;
}

void BatteryDecorator::update(double dt) {
    // call drone update function if battery not dead and drone available for delivery
    if (batteryLevel != 0 && sub->isAvailble()) {
        sub->update(dt);
        // if it can make the delivery without dying and the drone is scheduled for a delivery
    } else if (canMakeTrip(dt) && sub->isAvailble()==false) {
        sub->update(dt); // make delivery
    } else if (!canMakeTrip(dt) && sub->isAvailble()==false) {
        //go to nearest recharge station then make delivery
    }


    
    // check if it is charging and not full
    if(isCharging && isFull()) {
        // increase battery if charging
        charge(dt);
    } else {
        batteryLevel = batteryLevel - 2*dt;
    }
}

void BatteryDecorator::charge(double dt) {
    isCharging = true;
    batteryLevel = batteryLevel + 2*dt;
}

double BatteryDecorator::getBatteryLevel() {
    return batteryLevel;
}

bool BatteryDecorator::isFull() {
    if(batteryLevel == maxCapacity) {
        isCharging = false;
        return true;

    }
    return false;
}

double BatteryDecorator::calcTime() {
    //2*dt*(timeForDelivery + timeToRecharge) < batteryLevel then true  
    //distance is the path of the strategy
    double totalDist = 0;

    PathStrategy* packageStrat = sub->getPackageStrat(); //get package strategy
    std::vector<Vector3> packagePoints = packageStrat->getPoints();
    
    for (int i = 0; i < packagePoints.size()-1; i++) { //iterate through vector of points 
        totalDist += (packagePoints[i] - packagePoints[i+1]).magnitude(); //get distance of points and add
    }

    IStrategy* finalDestStrat = sub->getFinalDestStrat(); //get final destination strategy
    std::vector<Vector3> finalPoints = finalDestStrat->getPoints();
    for (int i = 0; i < finalPoints.size()-1; i++) { //iterate through vector of points 
        totalDist += (finalPoints[i] - finalPoints[i+1]).magnitude(); //get distance of points and add
    }
    
    return totalDist / sub->getSpeed(); 
}
//in istrat make an eta function that is pure virtual
//in path use same logic as above return time
//in celebration it is time + sub->strategy


//package location speed and distance tells how long 
bool BatteryDecorator::canMakeTrip(double dt) {
    double pathBattery = calcTime()*dt*2 ; //gets how much battery path will take
    double batteryThreshold = 25.0; //drone shouldn't make delivery if it causes battery to be lower than this
    if(pathBattery < batteryLevel - batteryThreshold) {
        return true;
    }
    return false;
}


bool BatteryDecorator::isDead() {
    if (batteryLevel == 0) {
        return true;
    }
    return false;
}
    