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
	char *m_PlanetName;
	//RGBImage m_Texture;
	CelestialBody *m_Satellite;
	//unsigned int m_TextureId;

	virtual void Draw(Position centerOfRevolution, unsigned int textId);
	virtual void Construct(float radius, float orbitRadius, float revolution, float rotation, char *planetName);
public:
	CelestialBody();
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName);
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, CelestialBody *satellite);
	virtual ~CelestialBody();  
	void Update(float elapsedTime, unsigned int textId);

	Position GetPosition() const;
	float GetOrbitRadius() const;
	char* GetPlanetName() const;
};

#endif // CELESTIAL_BODY_H
