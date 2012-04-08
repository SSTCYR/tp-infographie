#define GLUT_DISABLE_ATEXIT_HACK

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif

#include "SolarSystemManager.h"

SolarSystemManager::SolarSystemManager(int argc, char **argv, SolarSystem ss) : m_SolarSystem(ss)
{
	// Initialisation de GLUT
	glutInit(&argc, argv);

	// Initialisation de la fenetre
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GL_DEPTH);

	// Initialisation des fonctions de rappel
	glutMouseFunc(MouseClickFunc);
	glutMotionFunc(MouseMoveFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutDisplayFunc(DisplayFunc);

	// Initialisation de la camera

	glutMainLoop();
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

void SolarSystemManager::DisplayFunc()
{
}