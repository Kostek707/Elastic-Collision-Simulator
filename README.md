# Elastic Collision Simulator

By default, the program simulates the movement of 15 circles with different masses depending on their radius. To perform a simulation with different number of circles change the value assigned to the variable numberOfBalls. When the collision is detected, the program simulates the movement of the circles according to the equations that predicts the movement after the occurrence of an elastic collision, more information can be found  [here](https://en.wikipedia.org/wiki/Elastic_collision)

## Motivation

I was inspired to create this program after a discussion with a student from the Warsaw University of Technology. After the conversation, which concerned advantages of low-level programming over the modern approach of developing software using only high-level languages and frameworks I decided to create this physical engine from scratch. Creating this program allowed me to better understand the physical processes occurring during the collisions, as well as to learn more about such engines.

## Overview

![](https://i.imgur.com/A8tUgoc.gif)

## Getting started

Below you can find instructions on how to run the program on your computer.

### Prerequisites

To run the program, you must have an SFML library installed. You can install it on Linux using the command shown below

```
sudo apt-get install libsfml-dev
```

If you encounter any problems, refer to the SFML library [homepage](https://www.sfml-dev.org/tutorials/2.5/start-linux.php)

To install the SFML library on any other operating system, refer to this [page](https://www.sfml-dev.org/download.php) 

### How to run code on Linux

After downloading files or cloning the repository, compile the main.cpp file with the following command:

```
g++ -c main.cpp 
```

Link the compiled file to the SFML library in order to get the final executable:

```
g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
```

Finally, to run the program, use the command:
```
./sfml-app
```

## How to use?

After launching the program, you only need to catch one circle with the mouse and throw it towards another circle. After doing so just relax and admire the beauty of physics
