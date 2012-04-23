#ifndef RING_PLANET_H
#define RING_PLANET_H

#include "CelestialBody.h"

class RingPlanet : public CelestialBody
{
private:
	RGBImage m_Ring;
	unsigned int m_RingId;
protected:
	void Construct(float radius, float orbitRadius, float revolution, float rotation, char *planetName);
public:
	RingPlanet();
	RingPlanet(float radius, float orbitRadius, float revolution, float rotation, char *planetName);
	~RingPlanet();
	void Update(float elapsedTime, Position centerOfRevolution);
};

#endif // RING_PLANET_H
