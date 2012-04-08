#include "BitmapHandling.h"
#include "SolarSystem.h"
#include "SolarSystem_Config.h"
#include "RingPlanet.h"
#include "Sun.h"

SolarSystem::SolarSystem()
{
	CelestialBody mercury(MERCURY_EQUATOR_RADIUS, MERCURY_ORBIT_RADIUS, MERCURY_REVO_PERIOD, MERCURY_ROTATION_PERIOD, "mercury");

	CelestialBody venus(VENUS_EQUATOR_RADIUS, VENUS_ORBIT_RADIUS, VENUS_REVO_PERIOD, VENUS_ROTATION_PERIOD, "venus");

	CelestialBody moon(MOON_EQUATOR_RADIUS, MOON_ORBIT_RADIUS, MOON_REVO_PERIOD, MOON_ROTATION_PERIOD, "moon");

	CelestialBody earth(EARTH_EQUATOR_RADIUS, EARTH_ORBIT_RADIUS, EARTH_REVO_PERIOD, EARTH_ROTATION_PERIOD, "earth", &moon);

	CelestialBody mars(MARS_EQUATOR_RADIUS, MARS_ORBIT_RADIUS, MARS_REVO_PERIOD, MARS_ROTATION_PERIOD, "mars");

	CelestialBody jupiter(JUPITER_EQUATOR_RADIUS, JUPITER_ORBIT_RADIUS, JUPITER_REVO_PERIOD, JUPITER_ROTATION_PERIOD, "jupiter");

	RingPlanet saturn(SATURN_EQUATOR_RADIUS, SATURN_ORBIT_RADIUS, SATURN_REVO_PERIOD, SATURN_ROTATION_PERIOD, "saturn");

	RingPlanet uranus(URANUS_EQUATOR_RADIUS, URANUS_ORBIT_RADIUS, URANUS_REVO_PERIOD, URANUS_ROTATION_PERIOD, "uranus");

	CelestialBody neptune(NEPTUNE_EQUATOR_RADIUS, NEPTUNE_ORBIT_RADIUS, NEPTUNE_REVO_PERIOD, NEPTUNE_ROTATION_PERIOD, "neptune");

	CelestialBody pluto(PLUTO_EQUATOR_RADIUS, PLUTO_ORBIT_RADIUS, PLUTO_REVO_PERIOD, PLUTO_ROTATION_PERIOD, "pluto");

	Sun sun(SUN_EQUATOR_RADIUS, SUN_ORBIT_RADIUS, SUN_ROTATION_PERIOD, "sun");

	LoadBmp("Resources/texture_starbg.bmp", m_SkyBox);
}

SolarSystem::~SolarSystem()
{

}

void SolarSystem::UpdateScene(float elapsedTime)
{
	for(unsigned int i = 0; i < m_Bodies.size(); i++)
	{
		m_Bodies[i].Update(elapsedTime);
	}
}

inline vector<CelestialBody> SolarSystem::GetBodies() const
{
	return m_Bodies;
}
