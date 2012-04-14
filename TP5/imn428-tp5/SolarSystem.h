#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <vector>

#include "Camera.h"
#include "CelestialBody.h"
#include "RGBImage.h"
#include "SolarSystemTimer.h"

using namespace std;

class SolarSystem
{
private:
	CelestialBody m_Bodies[10];
	RGBImage m_SkyBox;
public:
	SolarSystem();
	~SolarSystem();
	
	void UpdateScene(float elapsedTime);
	//vector<CelestialBody> GetBodies() const;
	CelestialBody GetBody(int index) const;
};

#endif // SOLAR_SYSTEM_H
