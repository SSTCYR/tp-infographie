#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <vector>

#include "Camera.h"
#include "CelestialBody.h"
#include "SolarSystemTimer.h"
#include "Sun.h"

using std::vector;

class SolarSystem
{
private:
	Sun m_Sun;
	vector<CelestialBody> m_Planets;
	Timer m_Timer;
	Camera m_Camera;
public:
	SolarSystem();
	~SolarSystem();
	void RenderScene();
};

#endif // SOLAR_SYSTEM_H
