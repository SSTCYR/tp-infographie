#ifndef SOLAR_SYSTEM_MANAGER_H
#define SOLAR_SYSTEM_MANAGER_H

#include "Camera.h"
#include <vector>
using namespace std;

class SolarSystemManager
{
private:
	Camera *m_Camera;
public:
	SolarSystemManager();
	
	void KeyboardFunc(unsigned char key, int x, int y);
	void MouseMoveFunc(int x, int y);
	void MouseClickFunc(int button, int state, int x, int y);
};

#endif // SOLAR_SYSTEM_MANAGER_H
