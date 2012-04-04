#ifndef CAMERA_H
#define CAMERA_H

#include "CelestialBody.h"
#include "Utility.h"

class Camera
{
private:
	bool m_Fixed;
	CelestialBody m_CurrentFocus;
	Position m_Position;
	
	void ChangeFocus(int planetIndex, bool fixed);
	void Rotate();
	void Zoom();
public:
	Camera();
	Camera(CelestialBody focus);
	~Camera();
	void KeyboardFunc();
	void MouseMoveFunc();
	void MouseClickFunc();
};

#endif // CAMERA_H
