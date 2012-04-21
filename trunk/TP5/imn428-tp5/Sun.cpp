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

void Sun::Draw(Position centerOfRevolution, unsigned int textId)
{
	CelestialBody::Draw(centerOfRevolution, textId);
}

void Sun::Construct(float radius, float orbitRadius, float rotation, char *planetName)
{
	CelestialBody::Construct(radius, 0, rotation, 0, planetName);
	
	char billboardName[30];
	strcpy(billboardName, "Resources/billboard_");
	strcat(billboardName, planetName);
	strcat(billboardName, ".bmp");

	LoadBmp(billboardName, m_Billboard);
}
