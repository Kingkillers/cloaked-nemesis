#ifndef RPG_ENTITY_H
#define RPG_ENTITY_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "functions.h"
#include "world.h"

enum MoveDirections {
	MOVE_STAY,
	MOVE_UP,
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_LEFT,
	NUM_MOVE_DIRECTIONS
};
enum MoveTypes {
	MOVE_STILL,
	MOVE_ERRATIC,
	MOVE_PATH,
	NUM_MOVE_TYPES
};

class Entity
{
public:

	// SFML properties
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Color color;
	int texture_x, texture_y;

	// Position and movement
	int display_x, display_y, x, y;
	int move_type;

	Entity();
	void load();
	virtual void setPosition( int new_x, int new_y, World *world = NULL, sf::RenderWindow *window = NULL );
	bool inViewport( World *world );

	void act( World *world );
	bool move( int direction, World *world, sf::RenderWindow *window = NULL );
	int displayX();
	int displayY();
};

#endif
