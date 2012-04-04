#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "RGBImage.h"
#include "SolarSystemTimer.h"

struct Position
{
	double X;
	double Y;
	double Z;
};

class CelestialBody
{
private:
	Position m_Position;
	RGBImage m_Texture;
	RGBImage m_Ring;
	Timer m_Timer;

	void InitRing();
public:
	CelestialBody();
	CelestialBody(float radius, float orbitRadius, float revolution, float rotation);
	CelestialBody(float radius, float orbitRadius, float revolution, float rotation, CelestialBody satellite);
	CelestialBody(float radius, float orbitRadius, float revolution, float rotation, RGBImage ring);
	~CelestialBody();
	Position GetPosition();
};

#endif // CELESTIAL_BODY_H
