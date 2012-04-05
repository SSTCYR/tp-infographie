#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include <vector>

#include "RGBImage.h"
#include "SolarSystemTimer.h"
#include "Structs.h"

using std::vector;

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
	Timer *m_Timer;
	vector<CelestialBody> m_Satellites;

	void InitRing();
public:
	CelestialBody();
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, Timer *timer, bool hasRing);
	CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, Timer *timer, vector<CelestialBody> satellites);
	CelestialBody(float radius,	float orbitRadius, float rotation, char *planetName, Timer *timer, vector<CelestialBody> satellites);
	~CelestialBody();  
	Position GetPosition() const; 
	vector<CelestialBody> GetSatellites() const;
	void Update();
};

#endif // CELESTIAL_BODY_H
