#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "RGBImage.h"
#include "SolarSystemTimer.h"
#include "Structs.h"

class CelestialBody
{
protected:
	float m_Radius;
	float m_OrbitRadius;
	float m_Revolution;
	float m_Rotation;
	Position m_Position;
	RGBImage m_Texture;
	CelestialBody *m_Satellite;

	virtual void Draw(Position centerOfRevolution);
	virtual void Construct(float radius, float orbitRadius, float revolution, float rotation, char *planetName);
public:
	CelestialBody();
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName);
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, CelestialBody *satellite);
	virtual ~CelestialBody();  
	void Update(float elapsedTime);

	Position GetPosition() const;
	float GetOrbitRadius() const;
};

#endif // CELESTIAL_BODY_H
