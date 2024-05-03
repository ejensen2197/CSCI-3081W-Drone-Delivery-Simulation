# team-001-58-finalproject

Members: Ethan Jensen, Kent Nguyen, Sam Roberts, Hyunwoo Yang

X500's: jens2543, nguy4773, robe2210, yang6316

__PROJECT OVERVIEW__

The project is a simulation of a Drone Delivery System that includes packages to be delivered and robots who are the recipients of the packages. 
It also includes other features to make the simulation seem more lively as humans/helicopters/thiefs move around and interact during the simulation. 



__HOW TO RUN SIMULATION__

To build the simulation, navigate to the project directory team-001-58-finalproject on any Keller Hall lab machine and 
then write the following into the terminal:


# make -j

After that, to run the simulation, type the following command into the terminal:


# make run


This should start the program for the simulation. 
After it is started, open up a web browser and put the following into the search bar and hit enter:

# 127.0.0.1:8081 or 127.0.0.1:8082

This address should load the page of simulation. There should be a box for navigation at the top right. To schedule a delivery. Select the "Schedule Trip" button, enter a name for delivery, and select a pathing strategy. Click a starting point on the map and a destination point of delivery. Finally, clicking the "Submit" button will schedule the delivery of package. The drone in the simulation with path towards the package, pick it up, and deliver it to the robot. Clicking the "Add Human" button will add more humans to the simulation. This works with the porch pirate simulation, where a pirate can come and steal a package if it is in the radius.


# Simulation Features

__Drones__

_A Drone will spawn whenever the simulation is created. Drones in the simulation will receive delivery requests through 
the scheduling page at the top right. The drones use many different pathing strategies such as: Astar, Beeline, Dijkstra, Breadth First Search,
and Depth First Search to retrieve packages and deliver those packages to robots. 
Depending on the drone's pathing strategy, the drone when completing a delivery will celebrate by either spinning or jumping._


__Packages__ 

Packages will spawn whenever a delivery is scheduled. The packages can be picked up by drones and then delivered to the robots.

__Helicopters__ 

A Helicopter will spawn whenever the simulation is created. The helicopter moves randomly around in the air while the simulation is running. 

__Robots__

Robots spawn whenever the delivery is scheduled and will move towards the package destination. The robot will receive the package once the delivery is complete. 

__Humans__

A Human spawns whenever the simulation is created. More humans can be spawned by pressing the "Add Human" button located at the top right of the simulation screen. A lot of humans can be added to the simulation, however, it may cause the simulation to lag. Humans will path randomly around. The porch pirates are colored red in the simulation and these humans are able to "steal" packages delivered by the drone if the pirate is in range of the delivered package. The pirates continue to move around randomly. 

__Recharge Station__ 

The recharge stations spread out around the campus and will serve as a place to recharge the battery of the drone once it hits a threshold. The drone will path to the recharge station and then charge to full battery.

__Porch Pirates__

These are the humans colored "red" in the simulation. More porch pirates can be added by clicking the "Add Human" button. These porch pirates roam and move randomly on the ground. They are able to steal delivered packages if they are in range. The range is super small because it represents a real-life scenario where you have to be close enough to the package to know that it is there. So the porch pirate will be notified that there is a package within it's radius and then it will path towards the package to attempt a steal. 

__Observers__

The observers watch all of the entities happening in the simulation and report it as a notification. For example, "Drone picked up: test_package" would indicate that the drone has picked up the package for a delivery. "Helicopter has traveled 5 miles" would indicate that the helicopter has been flying around the simulation for 5 miles. 

__Pathing Strategies__

The entities use one of the 5 pathing strategy design patterns: DFS, BFS, Dijkstra's, Beeline, and Astar. When scheduling a package for delivery, a choice between the 5 pathing strategies can be selected.

__Celebration__

The drone will celebrate whenever a package is delivered at the destination. The celebrations are Jump and Spin, or a combination of them. The celebration depends on the pathing strategy used to deliver the package. 


__New Features__

Feature 1: Recharge Station

_Functionality:_ The drone has a battery life and the recharge station is a way for the drone to recharge it's battery in order to deliver packages. 

_Significance:_ This represents a real life scenario where delivery vehicles will eventually run out of gas from delivery packages to customers. These delivery vehicles will need to refuel in order to keep delivering more packages. 

_Design Pattern(s):_ We used the decorator design pattern for the recharge stations and implemented most of the logic into the simulation model. We used this pattern because it allowed us to extend the project without modifying any of the original code. We just added on new logic. 

_How to use:_ After a few package deliveries in the simulation, the drone will start to decrease in battery life and it will automatically navigate to a recharge station to recharge in order to deliver more packages. 


Feature 2: Porch Pirates

_Functionality:_ These are humans that roam around the simulation and are able to "steal" delivered packages if they are within range of the package. 

_Significance:_ This represents a real life scenario where packages that are delivered can be stolen by other people before you are able to pick it up. 

_Design Pattern(s):_ We used an observer pattern that would notify the porch pirates that there is a package delivery. Only the thieves that are within range of the package are able to move towards the package and steal it. We chose this pattern because it would be easier to use the notification system that was already implemented and just extend it to notify a thief that it is able to steal a package. 

_How to use:_ Schedule a delivery and wait to see if there are porch pirates within radius to steal the package. An easier way to see the implementation would be to add a few humans to the simulation so that there are more thieves running around. If a thief is in the small radius of the delivered package, then it can move towards the package and steal it before the robot gets there. 

# Sprint Retrospective 

__What worked well__

The structure of the sprint was setup well and it made it easy to follow during our implementation. The tasks throughout the sprint were assigned evenly to allow for everyone to work on different tasks which allowed us to help each other. This allowed us to stay on top of implementations and what implementations still needed to be added.

__What didn't go as well__

Although the sprint helped us complete the tasks, we didn't use it to the best of it's ability. We could have updated the board and completed the tasks in a much timelier manner. There were a few tasks that may have gotten pushed to the next sprint because it wasn't completed on time. 

__What we would try next time__

We would try to all complete tasks within the same implementations so it is easier to understand. Sometimes it is harder to understand implementations from other people and what else they want to do with it. We would also make sure that tasks are done much quicker since some of the tasks were pushed to the next sprint because it was still "early" in the project timeline. This would result in a much cleaner schedule and would open up more time to ask questions and work on the project at a reasonable pace. 

# UML Diagram

link pdf:


# Docker

The Docker link to our public repo can be accessed here:
https://hub.docker.com/repository/docker/sjroberts2004/team-001-58-final-project/general
the link could be pulled as follows, replace x with file destination

# docker pull x/team-001-58-final-project:latest

of course this is after login.

# Presentation

This is the video presentation of the project and the new features that we implemented with demonstration:

https://www.youtube.com/watch?v=k8DQGWb4i9o
