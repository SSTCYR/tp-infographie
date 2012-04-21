#ifndef SOLAR_SYSTEM_MANAGER_H
#define SOLAR_SYSTEM_MANAGER_H

#include "CelestialBody.h"
#include "RingPlanet.h"
#include "Sun.h"
#include "Camera.h"
#include "RGBImage.h"
#include <vector>
using namespace std;

class SolarSystemManager
{
private:
	Camera *m_Camera;
	CelestialBody m_Bodies[10];
	RGBImage m_SkyBox;
	unsigned int m_TextureId[10];
	RGBImage m_Texture[10];
public:
	SolarSystemManager();
	//SolarSystemManager(SolarSystem ss);
	
	void CreateSolarSystem();
	void InitTexture();
	void KeyboardFunc(unsigned char key, int x, int y);
	void MouseMoveFunc(int x, int y);
	void MouseClickFunc(int button, int state, int x, int y);
	void DisplayFunc();
};

#endif // SOLAR_SYSTEM_MANAGER_H
