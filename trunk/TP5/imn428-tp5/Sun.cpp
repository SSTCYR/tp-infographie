#include "Sun.h"
#include "BitmapHandling.h"

Sun::Sun()
{}

Sun::Sun(float radius, float orbitRadius, float rotation, char *planetName)
{
	Construct(radius, orbitRadius, rotation, planetName);
}

Sun::~Sun(void)
{
}

void Sun::Update(float elapsedTime, Position centerOfRevolution)
{
	CelestialBody::Update(elapsedTime, centerOfRevolution);
}

void Sun::Construct(float radius, float orbitRadius, float rotation, char *planetName)
{
	CelestialBody::Construct(radius, 0, 1, rotation, planetName);
}
