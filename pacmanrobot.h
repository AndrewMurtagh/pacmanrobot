#ifndef PACMAN_ROBOT_H
#define PACMAN_ROBOT_H

#include <SFML/Graphics.hpp>
#include "pacmanmap.h"





class PacmanRobot {
public:
	PacmanRobot(const PacmanMap&);
	~PacmanRobot();

	void turnLeft();
	void turnRight();
	void moveForward();
	void moveBackward();
	float getFrontSensor();
	float getLeftSensor();
	float getRightSensor();
	void terminate();
	sf::Vector3f getPose();
	void setLinearSpeed(float);
	float getLinearSpeed() const;
	void setAngularSpeed(float);
	float getAngularSpeed() const;
	inline void setMaxSensorDistance(const float d) { max_distance = d; }
	inline float getMaxSensorDistance() const { return max_distance; }
	float getAngleToGoal();
	float getDistanceToGoal(); 
	bool isAtGoal();

	
	void toggleSensors();
	void draw(sf::RenderWindow&);

protected:

private:
    sf::CircleShape shape;
    sf::RectangleShape rect;
    sf::Vector3f pose;
    float speed;
    float ang_speed;
    bool over_;

    const PacmanMap& map;

    float sensor_distances[3];
    bool show_sensors;
    float max_distance;

};


#endif