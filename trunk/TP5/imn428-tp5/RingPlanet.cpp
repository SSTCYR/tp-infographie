#include "RingPlanet.h"
#include "BitmapHandling.h"

RingPlanet::RingPlanet()
{
}

RingPlanet::RingPlanet(float radius, float orbitRadius, float revolution, float rotation, char *planetName)
{
	Construct(radius, orbitRadius, revolution, rotation, planetName);
}

RingPlanet::~RingPlanet()
{
}

// TODO : Draw ring
void RingPlanet::Draw(Position centerOfRevolution)
{
	CelestialBody::Draw(centerOfRevolution);
}

void RingPlanet::Construct(float radius, float orbitRadius, float revolution, float rotation, char *planetName)
{
	LoadBmp(strcat(strcat("Resources/ring_", planetName), ".bmp"), m_Ring);
	CelestialBody::Construct(radius, orbitRadius, revolution, rotation, planetName);
}
