#ifndef RPG_SMOKE_H
#define RPG_SMOKE_H

#include <Thor/Math.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Vectors/PolarVector.hpp>

class SmokeSystem : public thor::ParticleSystem
{
public:

	SmokeSystem(const sf::Texture& texture) : thor::ParticleSystem(texture)
	{
		// Fade from mostly transparent white to completely transparent
		thor::ColorGradient gradient;
		gradient[0.f] = sf::Color(255, 255, 255, 10);
		gradient[1.f] = sf::Color(255, 255, 255, 0);

		// Fade and grow slightly larger over time
		thor::ColorAnimation colorizer(gradient);
		this->addAffector(thor::AnimationAffector(colorizer));
		this->addAffector(thor::ScaleAffector(sf::Vector2f(1.4f, 0.f)));
	}
};

class SmokeEmitter : public thor::UniversalEmitter
{
public:

	SmokeEmitter() : thor::UniversalEmitter()
	{
		this->setEmissionRate(15.f);
		this->setParticleLifetime(sf::seconds(2.f));

		// Send smoke vertically
		thor::PolarVector2f velocity(50.f, -90.f);
		this->setParticleVelocity(thor::Distributions::deflect(velocity, 30.f));
		//this->setParticleColor(sf::Color(255,200,200));
	}
};

class FireSystem : public thor::ParticleSystem
{
public:

	FireSystem(const sf::Texture& texture) : thor::ParticleSystem(texture)
	{
		// Fade from mostly transparent white to completely transparent
		thor::ColorGradient gradient;
		gradient[0.f] = sf::Color(255, 255, 200, 00);
		gradient[0.1f] = sf::Color(255, 255, 200, 50);
		gradient[0.2f] = sf::Color(255, 50, 0, 200);
		gradient[0.7f] = sf::Color(255, 00, 0, 100);
		gradient[1.f] = sf::Color(255, 00, 0, 40);

		// Fade and grow slightly smaller over time
		thor::ColorAnimation colorizer(gradient);

		this->addAffector(thor::AnimationAffector(colorizer));
		this->addAffector(thor::ScaleAffector(sf::Vector2f(-1.5f, -1.5f)));
	}
};

class FireEmitter : public thor::UniversalEmitter
{
public:

	FireEmitter() : thor::UniversalEmitter()
	{
		this->setEmissionRate(10.f);
		this->setParticleLifetime(sf::seconds(.5f));

		// Send fire vertically
		thor::PolarVector2f velocity(80.f, -90.f);
		this->setParticleVelocity(thor::Distributions::deflect(velocity, 25.f));
		//this->setParticleColor(sf::Color(255,200,200));
	}
};

#endif
