#include "BitmapHandling.h"
#include "SolarSystem.h"
#include "SolarSystem_Config.h"

SolarSystem::SolarSystem()
{
	/*m_Timer = Timer::GetInstance();

	CelestialBody mercury(MERCURY_EQUATOR_RADIUS, MERCURY_ORBIT_RADIUS, MERCURY_REVO_PERIOD, MERCURY_ROTATION_PERIOD, 
		"mercury", m_Timer, false);

	CelestialBody venus(VENUS_EQUATOR_RADIUS, VENUS_ORBIT_RADIUS, VENUS_REVO_PERIOD, VENUS_ROTATION_PERIOD, 
		"venus", m_Timer, false);

	CelestialBody moon(MOON_EQUATOR_RADIUS, MOON_ORBIT_RADIUS, MOON_REVO_PERIOD, MOON_ROTATION_PERIOD, 
		"moon", m_Timer, false);

	vector<CelestialBody> satellites;
	satellites.push_back(moon);
	CelestialBody earth(EARTH_EQUATOR_RADIUS, EARTH_ORBIT_RADIUS, EARTH_REVO_PERIOD, EARTH_ROTATION_PERIOD, "earth", m_Timer, satellites);

	CelestialBody mars(MARS_EQUATOR_RADIUS, MARS_ORBIT_RADIUS, MARS_REVO_PERIOD, MARS_ROTATION_PERIOD, 
		"mars", m_Timer, false);

	CelestialBody jupiter(JUPITER_EQUATOR_RADIUS, JUPITER_ORBIT_RADIUS, JUPITER_REVO_PERIOD, JUPITER_ROTATION_PERIOD, 
		"jupiter", m_Timer, false);

	CelestialBody saturn(SATURN_EQUATOR_RADIUS, SATURN_ORBIT_RADIUS, SATURN_REVO_PERIOD, SATURN_ROTATION_PERIOD, 
		"saturn", m_Timer, false);

	CelestialBody uranus(URANUS_EQUATOR_RADIUS, URANUS_ORBIT_RADIUS, URANUS_REVO_PERIOD, URANUS_ROTATION_PERIOD, 
		"uranus", m_Timer, false);

	CelestialBody neptune(NEPTUNE_EQUATOR_RADIUS, NEPTUNE_ORBIT_RADIUS, NEPTUNE_REVO_PERIOD, NEPTUNE_ROTATION_PERIOD, 
		"neptune", m_Timer, false);

	CelestialBody pluto(PLUTO_EQUATOR_RADIUS, PLUTO_ORBIT_RADIUS, PLUTO_REVO_PERIOD, PLUTO_ROTATION_PERIOD, 
		"pluto", m_Timer, false);

	satellites.clear();
	satellites.push_back(mercury);
	satellites.push_back(venus);
	//satellites.push_back(earth);
	//satellites.push_back(mars);
	//satellites.push_back(jupiter);
	//satellites.push_back(saturn);
	//satellites.push_back(uranus);
	//satellites.push_back(neptune);
	//satellites.push_back(pluto);
	CelestialBody sun(SUN_EQUATOR_RADIUS, SUN_ORBIT_RADIUS, SUN_ROTATION_PERIOD, 
		"sun", m_Timer, satellites);

	m_Sun = sun;

	LoadBmp("Resources/texture_starbg.bmp", m_SkyBox);*/
}

SolarSystem::~SolarSystem()
{

}

void SolarSystem::UpdateScene(float elapsedTime)
{
}
