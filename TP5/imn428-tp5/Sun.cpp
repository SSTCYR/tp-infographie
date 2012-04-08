#include "Sun.h"
#include "BitmapHandling.h"

Sun::Sun()
{}

Sun::Sun(float radius, float orbitRadius, float rotation, char *planetName)
{
	LoadBmp(strcat(strcat("Resources/billboard_", planetName), ".bmp"), m_Billboard);
	CelestialBody::Construct(radius, 0, rotation, 0, planetName);
}

Sun::~Sun(void)
{
}
