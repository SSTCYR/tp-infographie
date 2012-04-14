#define GLUT_DISABLE_ATEXIT_HACK

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif
#include "SolarSystem_Config.h"
#include "SolarSystemManager.h"
#include "BitmapHandling.h"

SolarSystemManager::SolarSystemManager()
{
	//Remettre ca dans le systeme solaire si possible
	CreateSolarSystem();
}
/*
SolarSystemManager::SolarSystemManager(SolarSystem ss) : m_SolarSystem(ss)
{
}
*/
void SolarSystemManager::CreateSolarSystem()
{
	CelestialBody mercury(MERCURY_EQUATOR_RADIUS, MERCURY_ORBIT_RADIUS, MERCURY_REVO_PERIOD, MERCURY_ROTATION_PERIOD, "mercury", 1);
	m_Bodies[1] = mercury;
	CelestialBody venus(VENUS_EQUATOR_RADIUS, VENUS_ORBIT_RADIUS, VENUS_REVO_PERIOD, VENUS_ROTATION_PERIOD, "venus", 2);
	m_Bodies[2] = venus;
	CelestialBody moon(MOON_EQUATOR_RADIUS, MOON_ORBIT_RADIUS, MOON_REVO_PERIOD, MOON_ROTATION_PERIOD, "moon",10);
	CelestialBody earth(EARTH_EQUATOR_RADIUS, EARTH_ORBIT_RADIUS, EARTH_REVO_PERIOD, EARTH_ROTATION_PERIOD, "earth", 3, &moon);
	m_Bodies[3] = earth;
	CelestialBody mars(MARS_EQUATOR_RADIUS, MARS_ORBIT_RADIUS, MARS_REVO_PERIOD, MARS_ROTATION_PERIOD, "mars", 4);
	m_Bodies[4] = mars;
	CelestialBody jupiter(JUPITER_EQUATOR_RADIUS, JUPITER_ORBIT_RADIUS, JUPITER_REVO_PERIOD, JUPITER_ROTATION_PERIOD, "jupiter", 5);
	m_Bodies[5] = jupiter;
	RingPlanet saturn(SATURN_EQUATOR_RADIUS, SATURN_ORBIT_RADIUS, SATURN_REVO_PERIOD, SATURN_ROTATION_PERIOD, "saturn", 6);
	m_Bodies[6] = saturn;
	RingPlanet uranus(URANUS_EQUATOR_RADIUS, URANUS_ORBIT_RADIUS, URANUS_REVO_PERIOD, URANUS_ROTATION_PERIOD, "uranus", 7);
	m_Bodies[7] = uranus;
	CelestialBody neptune(NEPTUNE_EQUATOR_RADIUS, NEPTUNE_ORBIT_RADIUS, NEPTUNE_REVO_PERIOD, NEPTUNE_ROTATION_PERIOD, "neptune", 8);
	m_Bodies[8] = neptune;
	CelestialBody pluto(PLUTO_EQUATOR_RADIUS, PLUTO_ORBIT_RADIUS, PLUTO_REVO_PERIOD, PLUTO_ROTATION_PERIOD, "pluto", 9);
	m_Bodies[9] = pluto;
	Sun sun(SUN_EQUATOR_RADIUS, SUN_ORBIT_RADIUS, SUN_ROTATION_PERIOD, "sun", 0);
	m_Bodies[0] = sun;

	LoadBmp("Resources/texture_starbg.bmp", m_SkyBox);

}

void SolarSystemManager::KeyboardFunc(unsigned char key, int x, int y)
{

}

void SolarSystemManager::MouseClickFunc(int button, int state, int x, int y)
{
	switch(button)
	{
		case (GLUT_LEFT_BUTTON):
		{
			if(state == GLUT_DOWN)
			{
			}
			break;
		}
		case (GLUT_MIDDLE_BUTTON):
		{
			if(state == GLUT_DOWN)
			{
			}
			break;
		}
		case (GLUT_RIGHT_BUTTON):
		{
			break;
		}
		default:
		{
			if(state == GLUT_DOWN)
			{
			}
			break;
		}

		glutPostRedisplay();
	}
}

void SolarSystemManager::MouseMoveFunc(int x, int y)
{
}

// TODO : Update with a real elapsed time value
void SolarSystemManager::DisplayFunc()
{
	glClearColor(0.3, 0.7, 1.0, 1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Initialisation de la camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(70,640/(float)480,200.0f,0.1f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//TODO fonction de repositionnement de camera (position et ou elle regarde)
	gluLookAt(	0,	-20,	20,
				0,	0,	0,
				0,	1,	0);

	//Light Setup
	glEnable(GL_LIGHT0);
	float		gtf_LightColor[4]	 = {1.0f, 1.0f, 1.0f, 1.0f};
	float		gtf_LightPosition[4] = {0.0f,0.0f,-10.0f,1.0f};
	glLightfv(	GL_LIGHT0,	GL_POSITION,		gtf_LightPosition);
	glLightfv(	GL_LIGHT0,	GL_DIFFUSE,			gtf_LightColor);
	glLightfv(	GL_LIGHT0,	GL_SPECULAR,		gtf_LightColor);
	glLightf(	GL_LIGHT0,	GL_SPOT_CUTOFF,		180.0f);
	
	for(int i = 0; i < 10; i++)
	{
		m_Bodies[i].Update(0.0);
	}

	glutSwapBuffers();
}
