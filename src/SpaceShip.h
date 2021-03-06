#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__
#include "DisplayObject.h"
#include "TextureManager.h"
//#include "Game.h"

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
	glm::vec2 getOrientation()const;
	void setOrientation(glm::vec2 Orientation);
	void setRotation(float Angle);
	float getRotation()const;
	float getTurnRate()const;
	void setTurnRate(float rate);
	float getAccelerationRate()const;
	void setAccelerationRate(float rate);
private:

	glm::vec2 m_destination;
	glm::vec2 m_TargetDirection;
	glm::vec2 m_Orientation;
	float m_RotationAngle;
	float m_MaxSpeed;
	float m_turnRate;
	float m_accelerationRate;
	void m_Move();
};
#endif // !__SPACE_SHIP__
