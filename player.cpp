#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:

	Player() : Entity()
	{
		texture_x = 0;
		texture_y = 0;
		color = sf::Color(0, 255, 0);
	}

	void load()
	{
		x = y = 5;
		this->setPosition(x, y);

		Entity::load();
	}

	/**
	 * Set position and adjust world viewport
	 */
	void setPosition( int new_x, int new_y, World *world = NULL, sf::RenderWindow *window = NULL )
	{
		x = new_x;
		y = new_y;
		int view_x = 0, view_y = 0;

		if( world != NULL && window != NULL ) {
			view_x = world->view_x;
			view_y = world->view_y;

			// Close to the border
			if( x > view_x+TILES_X-4 ) {
				view_x = x-5;
			}
			if( y > view_y+TILES_Y-4 ) {
				view_y = y-5;
			}
			if( x < view_x+3 ) {
				view_x = x+6-TILES_X;
			}
			if( y < view_y+3 ) {
				view_y = y+6-TILES_Y;
			}
			if( view_x > WORLD_X-TILES_X ) { view_x = WORLD_X-TILES_X; }
			if( view_y > WORLD_Y-TILES_Y ) { view_y = WORLD_Y-TILES_Y; }
			if( view_x < 0 ) { view_x = 0; }
			if( view_y < 0 ) { view_y = 0; }

			world->setViewport(view_x, view_y, window);
		}

		Entity::setPosition( new_x, new_y, world );
	}
};

#endif
