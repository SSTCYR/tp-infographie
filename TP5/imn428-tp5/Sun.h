#pragma once
#include "CelestialBody.h"
class Sun : public CelestialBody
{
private:
	RGBImage m_Billboard;
public:
	Sun();
	Sun(float radius, float orbitRadius, float rotation, char *planetName);
	~Sun();
};

