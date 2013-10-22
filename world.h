#ifndef RPG_WORLD_H
#define RPG_WORLD_H

#include <cmath>

#include "tilemap.cpp"

#define SCREENS_X 10
#define SCREENS_Y 10
#define TILES_X 25
#define TILES_Y 16
#define WORLD_X (SCREENS_X*TILES_X)
#define WORLD_Y (SCREENS_Y*TILES_Y)

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 512

class World
{
public:

	std::string tileset;				// tileset file name
	TileMap map;						// drawable map

	Tile world_tiles[1024];				// defines the tiles used by this map
	int num_world_tiles;				// total number of world tiles

	Tile level[WORLD_Y][WORLD_X];		// assigns one world_tile to each coordinate
	bool generated;

	int view_x, view_y;					// the top left corner of the viewport

	World();
	bool load();
	virtual void generate() { }
	bool render();
	Tile tileAt( int pos_x, int pos_y );
	void setViewport( int start_x, int start_y, sf::RenderWindow *window );
	void centerViewport( int center_x, int center_y, sf::RenderWindow *window );

	// Helpers for generating maps
	void generate_square( int start_x, int start_y, int end_x, int end_y, int border_tile_id, bool filled, int fill_tile_id );
};

#endif

