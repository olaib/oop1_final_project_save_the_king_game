#pragma once
#include "Objects/StaticObjects/StaticObject.h"

class Gift : public StaticObject {
public:
	using StaticObject::StaticObject;
	using StaticObject::handleCollision;
};