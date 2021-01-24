#include "SpaceShip.h"

Spaceship::Spaceship()
{
	TextureManager::Instance()->load("../Assets/textures/spaceship.png", "spaceship");
	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.f, 300.0f);
	getRigidBody()->velocity =glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);

}

Spaceship::~Spaceship()
= default;

void Spaceship::draw()
{
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y, 0, 255, true);
}

void Spaceship::update()
{
}

void Spaceship::clean()
{
}
