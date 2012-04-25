#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "RGBImage.h"
#include "SolarSystemTimer.h"
#include "Structs.h"
#include "SolarSystem_Config.h"

class CelestialBody
{
protected:
	float m_Radius;
	float m_OrbitRadius;
	float m_Revolution;
	float m_Rotation;
	Position m_Position;
	float m_RotationAngle;
	float m_RevolutionAngle;
	float m_RotationTime;
	float m_RevolutionTime;
	char *m_PlanetName;
	bool m_HasRing;


public:
	CelestialBody();
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, bool hasRing);
	virtual ~CelestialBody(); 

	void Update(float elapsedTime, Position centerOfRevolution);

	void DrawOrbit(Position centerOfRevolution);

	Position GetPosition() const;
	float GetOrbitRadius() const;
	float GetRadius() const;
	float GetRotation() const;
	float GetRevolution() const;
	float GetRotationAngle() const;
	float GetRevolutionAngle() const;
	char* GetPlanetName() const;
	bool HasRing() const;
};

#endif // CELESTIAL_BODY_H
