#ifndef RPG_TILE_H
#define RPG_TILE_H

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

enum TileTypes {
	TILE_TYPE_FLOOR,
	TILE_TYPE_WALL,
	//TILE_TYPE_DOOR,
	NUM_TILE_TYPES
};

class Tile
{
public:
	int id; // specific to each world
	int type; // one of TileTypes

	Tile()
	{
	}
};

#endif

