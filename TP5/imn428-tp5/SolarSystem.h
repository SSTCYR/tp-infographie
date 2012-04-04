#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <vector>

#include "Camera.h"
#include "CelestialBody.h"
#include "RGBImage.h"
#include "SolarSystemTimer.h"

class SolarSystem
{
private:
	CelestialBody *m_Sun;
	Timer m_Timer;
	Camera *m_Camera;
	RGBImage m_SkyBox;
public:
	SolarSystem();
	~SolarSystem();
	void RenderScene();
};

#endif // SOLAR_SYSTEM_H
