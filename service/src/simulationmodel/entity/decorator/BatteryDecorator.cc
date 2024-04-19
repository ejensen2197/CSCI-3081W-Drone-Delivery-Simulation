#include "BatteryDecorator.h"
#include "SimulationModel.h"

BatteryDecorator::BatteryDecorator(Drone* d) : IEntityDecorator(d) {
    batteryLevel = 100;
    maxCapacity = 100;
}

BatteryDecorator::~BatteryDecorator() {
    delete this->drone;
}

void BatteryDecorator::update(double dt) {
    

    //cases:
    //drone is not on delivery and is stationary = battery decreases less
    //drone is on delivery but cannot make the trip = recharge then finish delivery
    //drone is on delivery but can make trip = battery decreases and call drone update to make trip
    //drone is at recharge station before delivery
    //drone is at recharge station due to battery being below threshold
    
    // if at the recharge it should stay there and recharge until at full
    if (atRecharge) {
        if(batteryLevel == maxCapacity) {
            atRecharge = false;
        } else {
            batteryLevel += 2*dt;
        }
    } else if (batteryLevel != 0 && sub->isAvailable()) { // what if batteryLevel < 30??
         // call drone update function if battery not dead and drone available for delivery
        std::cout << "idle" << std::endl;
        sub->update(dt);
        this->batteryLevel -= 1*dt;
    } else if (canMakeTrip(dt) && sub->isAvailable()==false) {
        // if it can make the delivery without dying and the drone is scheduled for a delivery
        std::cout << "delivery scheduled" << std::endl;
        sub->update(dt); // make delivery
        this->batteryLevel -= 2*dt;
    } else if ((!canMakeTrip(dt) && sub->isAvailable()==false) || batteryLevel < 30) {
        // case for needing to recharge
        std::cout << "need recharge" << std::endl;
        findRecharge(dt);   
    } 
}

// void BatteryDecorator::charge(double dt) {
//     isCharging = true;
//     batteryLevel = batteryLevel + 2*dt;
// }

double BatteryDecorator::getBatteryLevel() {
    return batteryLevel;
}

bool BatteryDecorator::isFull() {
    if(batteryLevel == maxCapacity) {
        atRecharge = false;
        return true;
    }
    return false;
}

double BatteryDecorator::calcTime() {
    //2*dt*(timeForDelivery + timeToRecharge) < batteryLevel then true  
    //distance is the path of the strategy
    double totalDist = 0;

    IStrategy* packageStrat = sub->getPackageStrat(); //get package strategy
    totalDist += packageStrat->eta();

    IStrategy* finalDestStrat = sub->getFinalDestStrat(); //get final destination strategy
    totalDist += finalDestStrat->eta();
    std::cout << "total time: " << totalDist / sub->getSpeed() << std::endl;
    return totalDist / sub->getSpeed(); 
}

// make battery able to get anywhere when full so if drone can't make trip then go to recharge then make trip
// don;t need to calc recharge station logic as long as we make it so that the drone can make it to any recharge station if above threshold

//package location speed and distance tells how long 
bool BatteryDecorator::canMakeTrip(double dt) {
    double pathBattery = calcTime()*dt*2 ; //gets how much battery path will take
    double batteryThreshold = 25.0; //drone shouldn't make delivery if it causes battery to be lower than this
    if(pathBattery < batteryLevel - batteryThreshold) {
        std::cout << "Can make trip total battery need is: " << pathBattery << " total battery of drone: " << batteryLevel << std::endl;
        return true;
        
    }
    std::cout << "Cannot make trip" << std::endl;
    return false;
}


bool BatteryDecorator::isDead() {
    if (batteryLevel == 0) {
        return true;
    }
    return false;
}

// create find recharge function
// calls simulation model's nearest recharge function 
// nearest recharge takes in a Vector3 which is current position of drone needing recharge
// then iterates through vector of rechargeStation* and compares each location with drone location 
// it then returns vector3 of the closest recharge station's coordinates
// then the findRecharge function uses any strategy to move to the coordinates of the rechargeStation returned from the simulation model's func
void BatteryDecorator::findRecharge(double dt) {
    
    if(model) {
        Vector3 nearestRecharge = model->nearestRecharge(sub->getPosition()); //logic to get nearest recharge station
        if (rechargeStrategy == nullptr) {
            rechargeStrategy = new BeelineStrategy(sub->getPosition(), nearestRecharge); // strategy to nearest recharge station
        }
        rechargeStrategy->move(sub, dt); // move drone to recharge station
        batteryLevel -= 2*dt; 

        // checking that the drone arrived to recharge station also means strategy isCompleted
        if ((sub->getPosition() - nearestRecharge).magnitude() < 1.0) {
            atRecharge = true; // set to true so the update function knows to charge drone

            delete rechargeStrategy;
            rechargeStrategy = nullptr;
            if(sub->isAvailable() == false) {
               sub->setPackageStrat(); // calling new package creation
            }
            //SHOULD I CALL GET NEXT DELIVERY INSTEAD????

            // add logic to update strategy of to the package
        }


    }
}
    