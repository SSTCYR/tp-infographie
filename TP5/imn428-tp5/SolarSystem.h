#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <vector>

#include "Camera.h"
#include "CelestialBody.h"
#include "RGBImage.h"
#include "SolarSystemTimer.h"

using std::vector;

class SolarSystem
{
private:
	vector<CelestialBody> m_Bodies;
	RGBImage m_SkyBox;
public:
	SolarSystem();
	~SolarSystem();
	
	void UpdateScene(float elapsedTime);
	vector<CelestialBody> GetBodies() const;
};

#endif // SOLAR_SYSTEM_H
