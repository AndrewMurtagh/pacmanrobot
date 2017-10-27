#include <SFML/Graphics.hpp>
//#include <SFML/CircleShape.hpp>
#include <iostream>
#include <math.h>
#include "pacmanrobot.h"
#include "pacmanmap.h"

#define PI 3.14159265

template <typename T> 
inline T deg2rad(T num)
{
    return (PI/180.0f)*num;
}
template <typename T> 
inline T rad2deg(T num)
{
    return (180.0f/PI)*num;
}



PacmanRobot::PacmanRobot(const PacmanMap& map_) : map(map_) {
    
    pose = map.getStartingPose();

    over_ = false;
    max_distance = 125.f;
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
    if(over_) 
        return; 
    
    pose.z -= ang_speed;
    if(pose.z < 0) {
        pose.z = 360 - pose.z;
    }
    rect.setRotation(pose.z); 
}

void PacmanRobot::turnRight() {
    if(over_) 
        return; 
    
    pose.z += ang_speed;
    if(pose.z > 360) {
        pose.z -= 360;
    }
    rect.setRotation(pose.z); 
}
void PacmanRobot::moveForward() {
    if(over_) 
        return; 
    
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
    if(over_) 
        return; 
    
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
void PacmanRobot::terminate() {
    over_ = true;
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


float PacmanRobot::getAngleToGoal() {
    sf::Vector2f r2g(map.getGoalPosition().x -pose.x, pose.y-map.getGoalPosition().y);
    sf::Vector2f r2s(sin(deg2rad(pose.z)), cos(deg2rad(pose.z)));
    float dot = r2g.x*r2s.x + r2g.y*r2s.y;
    float r2g_norm = sqrt(pow(r2g.x, 2) + pow(r2g.y, 2));
    float r2s_norm = sqrt(pow(r2s.x, 2) + pow(r2s.y, 2));
    float cos_angle = dot/(r2g_norm*r2s_norm);
    bool left = (-r2g.x * r2s.y + r2g.y * r2s.x < 0);
    float angle = rad2deg(acos(cos_angle)); 
    return left ? -1*angle : angle;
    

}

float PacmanRobot::getDistanceToGoal() {
    float x1 = pose.x;
    float y1 = pose.y;
    float x2 = map.getGoalPosition().x;
    float y2 = map.getGoalPosition().y;
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

 
bool PacmanRobot::isAtGoal() {
    return map.robotIsAtGoal(pose);
}



void PacmanRobot::draw(sf::RenderWindow& window) {
    
    //sensors
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
    
    //to goal


    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].position = sf::Vector2f(pose.x, pose.y);
    line[0].color  = sf::Color::Magenta;
    line[1].position = sf::Vector2f(map.getGoalPosition().x, map.getGoalPosition().y);
    line[1].color = sf::Color::Magenta;
    window.draw(line);


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










/*
corridor following
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


/*
TODO: 
get/set sensor distance for each one

race, stages,  
moving goal, intermediate steps
simply connected maze

******angular speed bug*******

while vs if in game loop
badges
overload functions
maze finding algorithms

session 2:
main is now empty
poses
switch every 10 minutes
keep right sensor at const distance
minimise difference between left and right
explain game loop
line
get goal location function
help set up after class
comment out your solution and change the enum
pacman scoreboard
give them challenges and functions
remove timer
hand out - don't lose
*/





/*
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
      //  if (Keyboard::isKeyPressed(Keyboard::S)){
       //     pacman.toggleSensors();
        //}


		if (Keyboard::isKeyPressed(Keyboard::D)){
		    if(pacman.getLeftSensor() > pacman.getRightSensor()) {
		        pacman.turnLeft();
		    } else {
		        pacman.turnRight();
		    }
		    pacman.moveForward();
		}
		*/


        /*
        //one

		if(pacman.getPose().z != 180) {
			pacman.turnRight();
		} else {
			pacman.moveForward();
		}
        
        if(pacman.isAtGoal()) {
            pacman.terminate();
            std::cout << "Goal Reached!!!!!!!" << std::endl;
        }
        */
