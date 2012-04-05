#include "CelestialBody.h"

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, Timer *timer, bool hasRing) :
m_Radius(radius), m_OrbitRadius(orbitRadius), m_Revolution(revolution), m_Rotation(rotation)
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, Timer *timer, vector<CelestialBody> satellites) :
m_Radius(radius), m_OrbitRadius(orbitRadius), m_Revolution(revolution), m_Rotation(rotation), m_Satellites(satellites)
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float rotation, char *planetName, Timer *timer, vector<CelestialBody> satellites) :
m_Radius(radius), m_OrbitRadius(orbitRadius), m_Rotation(rotation), m_Satellites(satellites)
{
}

CelestialBody::~CelestialBody()
{
}

void CelestialBody::InitRing()
{
}

inline Position CelestialBody::GetPosition() const
{
	return m_Position;
}

inline vector<CelestialBody> CelestialBody::GetSatellites() const
{
	return m_Satellites;
}

void CelestialBody::Update()
{
}