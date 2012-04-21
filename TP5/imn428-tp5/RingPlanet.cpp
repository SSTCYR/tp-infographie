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
void RingPlanet::Draw(Position centerOfRevolution, unsigned int textId)
{
	CelestialBody::Draw(centerOfRevolution, textId);
}

void RingPlanet::Construct(float radius, float orbitRadius, float revolution, float rotation, char *planetName)
{
	CelestialBody::Construct(radius, orbitRadius, revolution, rotation, planetName);

	char ringName[30];
	strcpy(ringName, "Resources/ring_");
	strcat(ringName, planetName);
	strcat(ringName, ".bmp");

	LoadBmp(ringName, m_Ring);
}
