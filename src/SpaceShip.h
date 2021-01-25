#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__
#include "DisplayObject.h"
#include "TextureManager.h"

class Spaceship : public DisplayObject
{
public:
	Spaceship();
	~Spaceship();
	void draw() override;
	void update() override;
	void clean() override;

	void setDestination(const glm::vec2 destination);
	void setMaxSpeed(float speed);
private:

	glm::vec2 m_destination;
	glm::vec2 m_TargetDirection;
	float m_MaxSpeed;
	void m_Move();
};
#endif // !__SPACE_SHIP__
