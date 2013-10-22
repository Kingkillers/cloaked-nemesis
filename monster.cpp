#ifndef RPG_MONSTER_H
#define RPG_MONSTER_H

#include "entity.h"
#include "functions.h"

class Monster : public Entity
{
public:

	Monster() : Entity()
	{
		texture_x = 32;
		texture_y = 0;
		color = sf::Color(0, 0, 255);
	}

	void load()
	{
		int new_x = randNum(1, WORLD_X-2);
		int new_y = randNum(1, WORLD_Y-2);
		int move_type = (int)rand() % NUM_MOVE_TYPES;
		this->setPosition(new_x, new_y);
		this->move_type = move_type;

		Entity::load();
	}
};

#endif
