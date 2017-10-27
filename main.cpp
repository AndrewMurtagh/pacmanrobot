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





int main() {





    ////////////////////////////////////////////////////////
    ////////////////    ENTER CODE BELOW    ////////////////
    ////////////////////////////////////////////////////////
    PacmanMap map(PacmanMap::NINE);
    map.showMap(true);
    map.showGrid(false);

    PacmanRobot pacman(map);
    pacman.setLinearSpeed(4.5f);
    pacman.setAngularSpeed(1.0f);
    pacman.setMaxSensorDistance(125);
    ////////////////////////////////////////////////////////
    ////////////////    ENTER CODE ABOVE    ////////////////
    ////////////////////////////////////////////////////////





    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }






        ////////////////////////////////////////////////////////
        ////////////////    ENTER CODE BELOW    ////////////////
        ////////////////////////////////////////////////////////



        ////////////////////////////////////////////////////////
        ////////////////    ENTER CODE ABOVE    ////////////////
        ////////////////////////////////////////////////////////
        map.updatePoseText(pacman.getPose());
        map.updateSensorText(pacman.getLeftSensor(), pacman.getFrontSensor(), pacman.getRightSensor());
        map.updateGoalText(pacman.getAngleToGoal(), pacman.getDistanceToGoal());
        std::cout<<std::endl;
        window.clear();
        map.draw(window);
        pacman.draw(window);
        window.display();
    }




    return 0;
}

