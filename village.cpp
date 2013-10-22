#ifndef RPG_VILLAGE_H
#define RPG_VILLAGE_H

#include "world.h"

enum VillageTileTypes {
	VILLAGE_TILE_GRASS,
	VILLAGE_TILE_STONE_WALL,
	VILLAGE_TILE_WOOD_FLOOR,
	VILLAGE_TILE_MUD,
	VILLAGE_TILE_FENCE,
	VILLAGE_TILE_URN,
	VILLAGE_TILE_MARBLE_FLOOR,
	VILLAGE_TILE_COLUMN,
	NUM_VILLAGE_TILE_TYPES
};

class Village : public World
{
public:

	Village() : World()
	{
		tileset = "images/village.png";

		num_world_tiles = NUM_VILLAGE_TILE_TYPES;

		Tile grass;
		grass.id = VILLAGE_TILE_GRASS;
		grass.type = TILE_TYPE_FLOOR;
		world_tiles[VILLAGE_TILE_GRASS] = grass;

		Tile stone_wall;
		stone_wall.id = VILLAGE_TILE_STONE_WALL;
		stone_wall.type = TILE_TYPE_WALL;
		world_tiles[VILLAGE_TILE_STONE_WALL] = stone_wall;

		Tile wood_floor;
		wood_floor.id = VILLAGE_TILE_WOOD_FLOOR;
		wood_floor.type = TILE_TYPE_FLOOR;
		world_tiles[VILLAGE_TILE_WOOD_FLOOR] = wood_floor;

		Tile mud;
		mud.id = VILLAGE_TILE_MUD;
		mud.type = TILE_TYPE_FLOOR;
		world_tiles[VILLAGE_TILE_MUD] = mud;

		Tile fence;
		fence.id = VILLAGE_TILE_FENCE;
		fence.type = TILE_TYPE_WALL;
		world_tiles[VILLAGE_TILE_FENCE] = fence;

		Tile urn;
		urn.id = VILLAGE_TILE_URN;
		urn.type = TILE_TYPE_WALL;
		world_tiles[VILLAGE_TILE_URN] = urn;

		Tile marble_floor;
		marble_floor.id = VILLAGE_TILE_MARBLE_FLOOR;
		marble_floor.type = TILE_TYPE_FLOOR;
		world_tiles[VILLAGE_TILE_MARBLE_FLOOR] = marble_floor;

		Tile column;
		column.id = VILLAGE_TILE_COLUMN;
		column.type = TILE_TYPE_WALL;
		world_tiles[VILLAGE_TILE_COLUMN] = column;
	}

	void generate()
	{
		// Town wall
		generate_square(0, 0, WORLD_X-1, WORLD_Y-1, VILLAGE_TILE_STONE_WALL, true, VILLAGE_TILE_GRASS);

		// Temple
		generate_square(10, 4, 20, 12, VILLAGE_TILE_COLUMN, true, VILLAGE_TILE_MARBLE_FLOOR);

		// Chicken coop
		generate_square(100, 106, 118, 113, VILLAGE_TILE_FENCE, true, VILLAGE_TILE_MUD);

		level[13][12] = world_tiles[VILLAGE_TILE_URN];
		level[13][18] = world_tiles[VILLAGE_TILE_URN];

		generated = true;
	}
};

#endif

