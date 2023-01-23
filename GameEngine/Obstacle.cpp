#include "Obstacle.h"

Obstacle::Obstacle(GameObject* parent, std::string name)
	:GameObject(parent, name),
	DEFAULT_SPEED(0.63),
	SPEED(6.0f),
	MAX_SPEED(4.6f)
{
}

Obstacle::~Obstacle()
{
}
