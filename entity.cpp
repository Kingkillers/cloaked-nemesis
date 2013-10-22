#include "entity.h"

Entity::Entity()
{
}

void Entity::load()
{
	texture.loadFromFile("images/entities.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(texture_x, texture_y, 32, 32));
	sprite.setColor(color);
}

/**
 * Move entity to a new position
 */
void Entity::setPosition( int new_x, int new_y, World *world, sf::RenderWindow *window )
{
	x = new_x;
	y = new_y;

	/*if( world != NULL ) {
		display_x = x - world->view_x;
		display_y = y - world->view_y;
	}*/

	//sprite.setPosition(sf::Vector2f(display_x*TILE_WIDTH, display_y*TILE_HEIGHT));
	sprite.setPosition(sf::Vector2f(x*TILE_WIDTH, y*TILE_HEIGHT));
}

/**
 * Check if the entity is visible
 * view_x, view_y is the top left corner of the map
 */
bool Entity::inViewport( World *world ) {
	//if( display_x >= 0 && display_x <= TILES_X-1 &&
//		display_y >= 0 && display_y <= TILES_Y-1 ) {
		return true;
	//}
	//return false;
}

/**
 * Takes its turn
 */
void Entity::act( World *world )
{
	int direction;

	switch( move_type ) {
		case MOVE_ERRATIC:
			direction = randNum(MOVE_UP, MOVE_LEFT);
			this->move(direction, world);
			break;

		case MOVE_PATH:
		case MOVE_STILL:
		default:
			// Move "still" to update display position, etc.
			this->move(MOVE_STILL, world);
			break;
	}
}

/**
 * Attempt to move the entity in the given direction
 * If something is in the way, handle that action instead
 * @param  int  direction  the directin you are moving defined by enum MoveDirections
 * @param  int  view_x  the top left corner of the screen
 * @param  int  view_y  the top left corner of the screen
 */
bool Entity::move( int direction, World *world, sf::RenderWindow *window )
{
	int new_x, new_y,
		x_change = 0, y_change = 0;

	switch( direction ) {
		case MOVE_UP:
			y_change = -1;
			break;

		case MOVE_RIGHT:
			x_change = 1;
			break;

		case MOVE_DOWN:
			y_change = 1;
			break;

		case MOVE_LEFT:
			x_change = -1;
			break;

		case MOVE_STILL:
		default:
			break;
	}

	new_x = x + x_change;
	new_y = y + y_change;
	bool moved = true;

	// World boundaries
	if( new_x < 0 ||
		new_y < 0 ||
		new_x > WORLD_X-1 ||
		new_y > WORLD_Y-1 ) {
			moved = false;
	}
	// Wall in the way?
	if( world->tileAt(new_x, new_y).type == TILE_TYPE_WALL ) {
		moved = false;
	}

	if( moved ) {
		this->setPosition(new_x, new_y, world, window);
		return true;
	}
	else {
		return false;
	}
}
