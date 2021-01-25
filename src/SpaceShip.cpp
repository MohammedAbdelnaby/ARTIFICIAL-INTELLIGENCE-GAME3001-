#include "SpaceShip.h"
#include "Util.h"

Spaceship::Spaceship():m_MaxSpeed(10.0f)
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
	m_Move();
}

void Spaceship::clean()
{
}
void Spaceship::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void Spaceship::setMaxSpeed(const float speed)
{
	m_MaxSpeed = speed;
}

void Spaceship::m_Move()
{
	//direction with Magnitude
	m_TargetDirection = m_destination - getTransform()->position;
	//normalized direction
	m_TargetDirection = Util::normalize(m_TargetDirection);
	getRigidBody()->velocity = m_TargetDirection * m_MaxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}
