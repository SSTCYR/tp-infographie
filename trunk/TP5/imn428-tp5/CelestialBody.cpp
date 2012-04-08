#include "CelestialBody.h"

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, bool hasRing) :
m_Radius(radius), m_OrbitRadius(orbitRadius), m_Revolution(revolution), m_Rotation(rotation)
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, CelestialBody *satellite) :
m_Radius(radius), m_OrbitRadius(orbitRadius), m_Revolution(revolution), m_Rotation(rotation), m_Satellite(satellite)
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float rotation, char *planetName) :
m_Radius(radius), m_OrbitRadius(orbitRadius), m_Rotation(rotation)
{
}

CelestialBody::~CelestialBody()
{
}

void CelestialBody::InitRing()
{
}

void CelestialBody::Update()
{
}