#include "world.h"

World::World()
{
	generated = false;
}

bool World::load()
{
	return map.load(tileset);
	view_x = view_y = -1;
}

bool World::render()
{
	Tile viewport[WORLD_Y * WORLD_X];

	for( int i=0; i<WORLD_Y; i++ ) {
		for( int j=0; j<WORLD_X; j++ ) {
			viewport[j + i * WORLD_X] = level[i][j];
		}
	}

	return map.render(sf::Vector2u(32, 32), viewport, WORLD_X, WORLD_Y);
}

Tile World::tileAt( int pos_x, int pos_y )
{
	if( pos_x < 0 ||
		pos_y < 0 ||
		pos_x >= WORLD_X ||
		pos_y >= WORLD_Y ) {
			// throw exception
	}
	return level[pos_y][pos_x];
}

void World::setViewport( int start_x, int start_y, sf::RenderWindow *window )
{
	// Only if it changed
	if( view_x != start_x || view_y != start_y ) {
		view_x = start_x;
		view_y = start_y;

		/*view_x = start_x;
		view_y = start_y;
		Tile viewport[TILES_Y * TILES_X];

		for( int i=0; i<TILES_Y; i++ ) {
			for( int j=0; j<TILES_X; j++ ) {
				viewport[j + i * TILES_X] = level[start_y+i][start_x+j];
			}
		}

		map.setViewport(sf::Vector2u(32, 32), viewport, TILES_X, TILES_Y);*/

		sf::View game_view(sf::FloatRect((view_x*TILE_WIDTH), (view_y*TILE_HEIGHT), WINDOW_WIDTH, WINDOW_HEIGHT));
		window->setView(game_view);
	}
}

void World::centerViewport( int center_x, int center_y, sf::RenderWindow *window )
{
	int start_x = center_x-(TILES_X/2);
	int start_y = center_y-(TILES_Y/2);
	if( start_x > WORLD_X-TILES_X ) { start_x = WORLD_X-TILES_X; }
	if( start_y > WORLD_Y-TILES_Y ) { start_y = WORLD_Y-TILES_Y; }
	if( start_x < 0 ) { start_x = 0; }
	if( start_y < 0 ) { start_y = 0; }

	setViewport(start_x, start_y, window);
}

/**
 * Draw a square
 */
void World::generate_square( int start_x, int start_y, int end_x, int end_y, int border_tile_id, bool filled = true, int fill_tile_id = -1 )
{
	for( int i=start_y; i<=end_y; i++ ) {
		for( int j=start_x; j<=end_x; j++ ) {
			if( i == start_y || j == start_x || i == end_y || j == end_x ) {
				level[i][j] = world_tiles[border_tile_id];
			}
			else if( filled ) {
				level[i][j] = world_tiles[fill_tile_id];
			}
		}
	}
}
