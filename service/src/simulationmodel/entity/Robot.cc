#include "Robot.h"

Robot::Robot(const JsonObject& obj) : IEntity(obj) {}

void Robot::update(double dt) {}

void Robot::receive(Package* p) { package = p; } //check if package is stolen if false then set delivered to true 

// some sort of function for humans to receive a package pointer and that pointer is their target
// when on route it checks if the package var delivered is false, if true then stop path and continue randomally walking
// if false and makes it to the package then set stolen to true and celebrate
// robot has similar package function where it is checking if package is stolen as it makes its way to location
// if it is stolen robot will continue and stop and drop off location 
// drone checks if package is stolen  and if it is true a new pacakge will spawn at initial location
//drone will go back and deliver the package directly to the robot 

//how does range spawn work for robot?