#pragma once

#include "GameObject.hpp"
#include "Player.hpp"
#include "Wall.hpp"

class ObjectManager
{
public:
	void start(void);
	void run(void);


protected:
	std::vector<GameObject> objects;
	GameObject* top;
};