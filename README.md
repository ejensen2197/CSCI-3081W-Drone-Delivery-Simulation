# team-001-58-finalproject

Members: Ethan Jensen, Kent Nguyen, Sam Roberts, Hyunwoo Yang

X500's: jens2543, nguy4773, robe2210, yang6316

__PROJECT OVERVIEW__

The project is a simulation of a Drone Delivery System that includes packages to be delivered and robots who are the recipients of the packages. 
It also includes other features to make the simulation seem more lively as humans and helicopters move around and interact during the simulation. 

- ADD MORE?


__HOW TO RUN SIMULATION__

To build the simulation, navigate to the project directory team-001-58-finalproject on any Keller Hall lab machine and 
then write the following into the terminal:


# make -j

After that, to run the simulation, type the following command into the terminal:


# make run


This should start the program for the simulation. 
After it is started, open up a web browser and put the following into the search bar and hit enter:

# 127.0.0.1:8081


# Simulation Features

__Drones__

A Drone will spawn whenever the simulation is created. Drones in the simulation will receive delivery requests through 
the scheduling page at the top right. The drones use many different pathing strategies such as: Astar, Beeline, Dijkstra, Breadth First Search,
and Depth First Search to retrieve packages and deliver those packages to robots. 
Depending on the drone's pathing strategy, the drone when completing a delivery will celebrate by either spinning or jumping.


__Packages__ 

Packages spawn whenever a delivery is scheduled. The packages can be picked up by drones and then delivered to robots.

# Docker

The Docker link to our public repo can be accessed here:
https://hub.docker.com/repository/docker/sjroberts2004/team-001-58-final-project/general
the link could be pulled as follows, replace x with file destination

# docker pull x/team-001-58-final-project:latest

of course this is after login.
