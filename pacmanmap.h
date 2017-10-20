#ifndef PACMAN_MAP_H
#define PACMAN_MAP_H


#include <SFML/Graphics.hpp>




class PacmanMap {
public:

	enum session_e {
        LINE,
        RACE,
        MAZE
    };

	PacmanMap(session_e);
	~PacmanMap();

	void showMap(bool);
	void showGrid(bool);
	void draw(sf::RenderWindow&);
	bool isPointOccupied(int, int) const;
	bool robotIsAtGoal(sf::Vector3f);

protected:

private:

	session_e session_;
	bool show_map_;
	bool show_grid_;

	static const int GRID_SIZE = 16;
	static const int WINDOW_SIZE = 736;
	static const int GRID_LINE_THICKNESS = 1;
	int NUM_GRIDS;

	sf::RectangleShape start_region, goal_region;

	int* occupancy_grid;
	
};


#endif