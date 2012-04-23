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
	float m_Angle;
	float m_RotationTime;
	float m_RevolutionTime;
	char *m_PlanetName;
	CelestialBody *m_Satellite;


	virtual void Construct(float radius, float orbitRadius, float revolution, float rotation, char *planetName);
public:
	CelestialBody();
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName);
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, CelestialBody *satellite);
	virtual ~CelestialBody(); 

	virtual void Update(float elapsedTime);

	void DrawOrbit();



	Position GetPosition() const;
	float GetOrbitRadius() const;
	float GetRadius() const;
	float GetRotation() const;
	float GetRevolution() const;
	float GetAngle() const;
	char* GetPlanetName() const;
	boolean hadSatellite() const;
};

#endif // CELESTIAL_BODY_H