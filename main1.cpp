#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <bitset>
#include <time.h>
#include "pacmanrobot.h"
#include "pacmanmap.h"

using namespace sf;
const int WINDOW_SIZE = 736;
RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Pacman Robot!");
clock_t t1,t2;
float difference = 0.0f;
bool goal_reached = false;


int main() {





    ////////////////////////////////////////////////////////
    ////////////////    ENTER CODE BELOW    ////////////////
    ////////////////////////////////////////////////////////
    PacmanMap map(PacmanMap::MAZE);
    map.showMap(true);
    map.showGrid(false);

    PacmanRobot pacman(PacmanMap::MAZE, map);
    pacman.setLinearSpeed(4.5f);
    pacman.setAngularSpeed(3.7f);
    ////////////////////////////////////////////////////////
    ////////////////    ENTER CODE ABOVE    ////////////////
    ////////////////////////////////////////////////////////






    t1=clock(); 
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }






        ////////////////////////////////////////////////////////
        ////////////////    ENTER CODE BELOW    ////////////////
        ////////////////////////////////////////////////////////

        if (Keyboard::isKeyPressed(Keyboard::Up)){
            pacman.moveForward();
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)){
            pacman.moveBackward();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            pacman.turnRight();
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            pacman.turnLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::S)){
            pacman.toggleSensors();
        }



        if(map.robotIsAtGoal(pacman.getPose())) {
            goal_reached = true;
            std::cout << "Goal Reached!!!!!!!" << std::endl;
            std::cout << "You took " << difference/CLOCKS_PER_SEC << " seconds" << std::endl;
        }




        ////////////////////////////////////////////////////////
        ////////////////    ENTER CODE ABOVE    ////////////////
        ////////////////////////////////////////////////////////
        if(!goal_reached) {
            t2=clock();
            difference = ((float)t2)-((float)t1);
            std::cout << "Time: " << difference/CLOCKS_PER_SEC << " seconds" << std::endl;
        }
        

        std::cout<<std::endl;
        window.clear();
        map.draw(window);
        pacman.draw(window);
        window.display();
    }




    return 0;
}

