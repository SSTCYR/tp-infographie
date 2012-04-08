#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "RGBImage.h"
#include "SolarSystemTimer.h"
#include "Structs.h"

class CelestialBody
{
private:
	bool m_HasRing;
	float m_Radius;
	float m_OrbitRadius;
	float m_Revolution;
	float m_Rotation;
	Position m_Position;
	RGBImage m_Texture;
	RGBImage m_Ring;
	CelestialBody *m_Satellite;

	void Draw(Position centerOfRevolution);
	void InitRing();
public:
	CelestialBody();
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, bool hasRing);
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, CelestialBody *satellite);
	CelestialBody(float radius,	float orbitRadius, float rotation, char *planetName);
	~CelestialBody();  
	void Update();

	Position GetPosition() const;
};

#endif // CELESTIAL_BODY_H
