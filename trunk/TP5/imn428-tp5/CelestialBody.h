#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "RGBImage.h"
#include "SolarSystemTimer.h"
#include "Structs.h"
#include "SolarSystem_Config.h"

class CelestialBody
{
private:
	// Planet radius
	float m_Radius;

	// Radius of the planet orbit
	float m_OrbitRadius;

	// Revolution period of the planet
	float m_Revolution;

	// Rotation period of the planet
	float m_Rotation;

	// Current position of the planet
	Position m_Position;

	// Angle that the planet rotate during a measure of time
	float m_RotationAngle;

	// Angle that the planet travel during a measure of time
	float m_RevolutionAngle;

	// Where the planet is in its rotation
	float m_RotationTime;

	// Where the planet is in its revolution
	float m_RevolutionTime;

	// Name of the planet
	char *m_PlanetName;

	// Planet has a ring or not
	bool m_HasRing;

public:
	// Default Constructor
	CelestialBody();
	
	// Parametric constructor
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, bool hasRing);
	
	// Destructor
	virtual ~CelestialBody(); 

	// Update the position of the planet
	void Update(float elapsedTime, Position centerOfRevolution);

	// Draw the orbit of the planet
	void DrawOrbit(Position centerOfRevolution);

	// Accessors
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
