#ifndef SOLAR_SYSTEM_MANAGER_H
#define SOLAR_SYSTEM_MANAGER_H

#include "SolarSystem.h"
#include "Camera.h"

class SolarSystemManager
{
private:
	Camera *m_Camera;
	SolarSystem m_SolarSystem;
	
	static void KeyboardFunc(unsigned char key, int x, int y);
	static void MouseMoveFunc(int x, int y);
	static void MouseClickFunc(int button, int state, int x, int y);
	static void DisplayFunc();
public:
	SolarSystemManager(int argc, char **argv, SolarSystem ss);
};

#endif // SOLAR_SYSTEM_MANAGER_H
