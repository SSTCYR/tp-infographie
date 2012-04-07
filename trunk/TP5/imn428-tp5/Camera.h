#ifndef CAMERA_H
#define CAMERA_H

#define GLUT_DISABLE_ATEXIT_HACK

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif

#include "CelestialBody.h"
#include "Structs.h"

class Camera
{
private:
	bool m_IsFixed;
	CelestialBody m_CurrentFocus;
	Position m_Position;

	GLfloat	m_Theta;	
	GLfloat	m_Phi;	
	GLfloat	m_Distance;		
	GLfloat m_Fovy;   
	GLfloat m_Ratio;  
	GLfloat m_Znear;   
	GLfloat m_Zfar;
	
public:
	Camera();
	~Camera();
	
	void ChangeFocus(int planetIndex, bool fixed);
	void Rotate(int x, int y);
	void Zoom(int distance);
};

#endif // CAMERA_H
