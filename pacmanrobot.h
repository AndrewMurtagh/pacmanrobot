#ifndef PACMAN_ROBOT_H
#define PACMAN_ROBOT_H

#include <SFML/Graphics.hpp>
#include "pacmanmap.h"





class PacmanRobot {
public:
	PacmanRobot(PacmanMap::session_e, const PacmanMap&);
	~PacmanRobot();

	void turnLeft();
	void turnRight();
	void moveForward();
	void moveBackward();
	float getFrontSensor();
	float getLeftSensor();
	float getRightSensor();
	sf::Vector3f getPose();
	void setLinearSpeed(float);
	float getLinearSpeed() const;
	void setAngularSpeed(float);
	float getAngularSpeed() const;

	
	void toggleSensors();
	void draw(sf::RenderWindow&);

protected:

private:
    sf::CircleShape shape;
    sf::RectangleShape rect;
    sf::Vector3f pose;
    float speed;
    float ang_speed;

    const PacmanMap& map;

    float sensor_distances[3];
    bool show_sensors;
    static const float max_distance = 125.f;

};


#endif