#include "BatteryDecorator.h"

BatteryDecorator::BatteryDecorator(Drone* d) : IEntityDecorator(d) {
    batteryLevel = 100;
    maxCapacity = 100;
}

void BatteryDecorator::update(double dt) {
    //call drone update function
    sub->update(dt);

    // check if it is charging and not full
    if(isCharging && isFull()) {
        // increase battery if charging
        charge(dt);
    } else {
        batteryLevel = batteryLevel - 2;
    }
}

void BatteryDecorator::charge(double dt) {
    isCharging = true;
    batteryLevel = batteryLevel + 2;
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

bool BatteryDecorator::isDead() {
    if (batteryLevel == 0) {
        return true;
    }
    return false;
}
    