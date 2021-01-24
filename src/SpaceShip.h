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
};
#endif // !__SPACE_SHIP__
