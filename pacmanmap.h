#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H


#include <SFML/Graphics.hpp>




class PacmanMap {
public:

	
	enum challenge_enum {
        ONE,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN
    };

	PacmanMap(challenge_enum);
	~PacmanMap();

	void showMap(bool);
	void showGrid(bool);
	void draw(sf::RenderWindow&);
	bool isPointOccupied(int, int) const;
	bool robotIsAtGoal(sf::Vector3f) const;
	void updatePoseText(sf::Vector3f);
	void updateSensorText(int, int, int);
	void updateGoalText(float, float);
	//sf::RectangleShape getStartRect() const;
	sf::Vector2f getGoalPosition() const;
	sf::Vector3f getStartingPose() const;



	static const int GRID_SIZE = 16;

protected:

private:

	sf::Text pose_text_, sensor_text_, goal_text_, ch_text_;
	sf::Font font;

	challenge_enum challenge_;
	bool show_map_;
	bool show_grid_;

	static const int WINDOW_SIZE = 736;
	static const int GRID_LINE_THICKNESS = 1;
	int NUM_GRIDS;
	void buildMap(challenge_enum);
	void buildRegions(challenge_enum);

	sf::Color start_colour_;
	sf::RectangleShape start_region, goal_region;

	char* occupancy_grid;
	
};


#endif