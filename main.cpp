#include <cstdio>
#include <cstdlib>
#include <ctime>

extern "C" {
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
}

#include <Thor/Vectors/PolarVector.hpp>

#include "village.cpp"
#include "player.cpp"
#include "monster.cpp"
#include "smoke.cpp"

Village world;
Player player;
Monster monsters[100];

void completeTurn();

int main()
{
	srand(time(NULL));

	world.load();
	world.generate();
	world.render();

	player.load();
	for( int i=0; i<100; i++ ) {
		monsters[i].load();
	}
//	world.setViewport(0, 0);

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "RPG", sf::Style::Titlebar|sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	sf::Clock frameClock;

	world.setViewport(0, 0, &window);

	// Load texture
	sf::Texture texture;
	texture.loadFromFile("images/smoke.png");

	// For smoke
	SmokeSystem smoke_system(texture);
	SmokeEmitter smoke_emitter;

	FireSystem fire_system(texture);
	FireEmitter fire_emitter;

	sf::Vector2f position(200, 550);
	smoke_emitter.setParticlePosition(position);

	smoke_system.addEmitter(thor::refEmitter(smoke_emitter));
	fire_system.addEmitter(thor::refEmitter(fire_emitter));

	// run the main loop
	while( window.isOpen() )
	{
		// handle events
		sf::Event event;
		while( window.pollEvent(event) ) {
			if( event.type == sf::Event::Closed ) {
				window.close();
			}

			if( event.type == sf::Event::KeyPressed ) {
				switch( event.key.code ) {
					case sf::Keyboard::Escape:
						window.close();
						break;

					// Player movement
					case sf::Keyboard::Up:
						if( player.move(MOVE_UP, &world, &window) ) {
							completeTurn();
						}
						break;

					case sf::Keyboard::Right:
						if( player.move(MOVE_RIGHT, &world, &window) ) {
							completeTurn();
						}
						break;

					case sf::Keyboard::Down:
						if( player.move(MOVE_DOWN, &world, &window) ) {
							completeTurn();
						}
						break;

					case sf::Keyboard::Left:
						if( player.move(MOVE_LEFT, &world, &window) ) {
							completeTurn();
						}
						break;

					// Center viewport
					case sf::Keyboard::Slash:
						world.centerViewport(player.x, player.y, &window);
						break;

					case sf::Keyboard::F1:
						world.generate();
						break;

					case sf::Keyboard::F2:
						//world.save();
						break;

					case sf::Keyboard::F3:
						//world.load(player.world_y, player.world_x);
						break;

					default:
						break;
				}

				fire_system.clearParticles();
				sf::Vector2f position(16.f+(player.x*TILE_WIDTH), 16.f+(player.y*TILE_HEIGHT));
				fire_emitter.setParticlePosition(position);
			}

			if( event.type == sf::Event::MouseWheelMoved ) {
				sf::View current_view = window.getView();
				current_view.rotate(10.f * event.mouseWheel.delta);
				window.setView(current_view);
			}
		}

		// Update particle system and timer
		const sf::Time frameTime = frameClock.restart();
		smoke_system.update(frameTime);
		fire_system.update(frameTime);

		window.clear();
		window.draw(world.map);
		window.draw(player.sprite);
		window.draw(fire_system, sf::BlendAdd);
		window.draw(smoke_system, sf::BlendAdd);
		for( int i=0; i<100; i++ ) {
			if( monsters[i].inViewport(&world) ) {
				window.draw(monsters[i].sprite);
			}
		}
		window.display();
	}

	return 0;
}

void completeTurn()
{
	for( int i=0; i<100; i++ ) {
		monsters[i].act(&world);
		if( player.x == monsters[i].x && player.y == monsters[i].y ) {
			//
		}
	}
}
