#include <SFML/Graphics.hpp>
//#include <SFML/CircleShape.hpp>
#include <iostream>
#include <math.h>
#include "pacmanrobot.h"
#include "pacmanmap.h"

#define PI 3.14159265


double deg2rad(double degrees);

PacmanRobot::PacmanRobot(PacmanMap::session_e s, const PacmanMap& map_) : map(map_) {
    
    if(s == PacmanMap::LINE) {
        pose = sf::Vector3f(368, 40, 180);
    } else {
        pose = sf::Vector3f(48, 40, 180);
    }


    show_sensors = true;
    speed = 2.0f;
    ang_speed = 2.0f;
    float sensor_distances[3] = {0.0f};



    shape.setRadius(10.0f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin(sf::Vector2f(10.0f, 10.0f));

    rect.setOrigin(sf::Vector2f(1, 20));
    rect.setSize(sf::Vector2f(2, 20));
    rect.setFillColor(sf::Color::Yellow);

    shape.setPosition(sf::Vector2f(pose.x, pose.y));
    rect.setPosition(sf::Vector2f(pose.x, pose.y)); 
    rect.setRotation(pose.z); 
}

PacmanRobot::~PacmanRobot() {}



void PacmanRobot::turnLeft() {
    pose.z -= ang_speed;
    rect.setRotation(pose.z); 
}

void PacmanRobot::turnRight() {
    pose.z += ang_speed;
    rect.setRotation(pose.z); 
}
void PacmanRobot::moveForward() {
    float checkvalidx = pose.x + 10.0f*sin(deg2rad(pose.z));
    float checkvalidy = pose.y - 10.0f*cos(deg2rad(pose.z));
    if(!map.isPointOccupied(checkvalidx, checkvalidy)) {
        pose.x += speed*sin(deg2rad(pose.z));
        pose.y += -speed*cos(deg2rad(pose.z));
        sf::Vector2f vec = sf::Vector2f(speed*sin(deg2rad(pose.z)), -speed*cos(deg2rad(pose.z)));
        shape.move(vec); 
        rect.move(vec); 
    } 
}
void PacmanRobot::moveBackward() {
    float checkvalidx = pose.x - 10.0f*sin(deg2rad(pose.z));
    float checkvalidy = pose.y + 10.0f*cos(deg2rad(pose.z));


    if(!map.isPointOccupied(checkvalidx, checkvalidy)) {
        pose.x += -speed*sin(deg2rad(pose.z));
        pose.y += speed*cos(deg2rad(pose.z));
        sf::Vector2f vec = sf::Vector2f(-speed*sin(deg2rad(pose.z)), speed*cos(deg2rad(pose.z)));
        shape.move(vec); 
        rect.move(vec); 
    } 
}

float PacmanRobot::getLeftSensor() {
    return sensor_distances[0];

}
float PacmanRobot::getFrontSensor() {
    return sensor_distances[1];

}
float PacmanRobot::getRightSensor() {
    return sensor_distances[2];
}

sf::Vector3f PacmanRobot::getPose() {
    return pose;
}


void PacmanRobot::draw(sf::RenderWindow& window) {
    

    float angles[3] = {-90.0f, 0.0f, 90.0f};
    for(int i=0; i<3; i++) {
        bool occ = false;
        float thisdist = 0.0f;
    
        float check_point_x = pose.x;
        float check_point_y = pose.y;
        while(thisdist < max_distance) {
            check_point_x = pose.x + thisdist*sin(deg2rad(pose.z+angles[i]));
            check_point_y = pose.y - thisdist*cos(deg2rad(pose.z+angles[i]));
            
            occ = map.isPointOccupied(check_point_x, check_point_y);
            sensor_distances[i] = thisdist;
            if(occ == true) {
               // thisdist -= 2.0f;
               break;
            }
            
            
            thisdist += 2.0f;
        }


        if(show_sensors) {
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0].position = sf::Vector2f(pose.x, pose.y);
            line[0].color  = sf::Color::Red;
            line[1].position = sf::Vector2f(check_point_x, check_point_y);
            line[1].color = sf::Color::Red;
            window.draw(line);

        }
    }
    


    window.draw(shape);
    window.draw(rect);
}



void PacmanRobot::setLinearSpeed(float s) {
    if(s > 15) {
        speed = 15;
    } else {

        speed = s;
    }
}

float PacmanRobot::getLinearSpeed() const {
    return speed;
}

void PacmanRobot::setAngularSpeed(float s) {
    if(s > 7.5f) {
        ang_speed = 7.5f;
    } else {

        ang_speed = s;
    }
}

float PacmanRobot::getAngularSpeed() const {
    return ang_speed;
}


void PacmanRobot::toggleSensors() {
    show_sensors = show_sensors ? false : true;
}





double deg2rad(double degrees) {
    return (PI/180.0f)*degrees;
}


/*
if (Keyboard::isKeyPressed(Keyboard::D)){
    clock_started = true; // NO NEED TO TOUCH THIS
    
    if(pacman.getLeftSensor() > pacman.getRightSensor()) {
        pacman.turnLeft();
    } else {
        pacman.turnRight();
    }
    pacman.moveForward();
}
*/