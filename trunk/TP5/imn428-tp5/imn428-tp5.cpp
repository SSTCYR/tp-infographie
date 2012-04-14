#include "SolarSystem.h"
#include "SolarSystemManager.h"
#include <vector>
using namespace std;

void KeyboardFunc(unsigned char key, int x, int y);
void MouseMoveFunc(int x, int y);
void MouseClickFunc(int button, int state, int x, int y);
void DisplayFunc();

//SolarSystemManager *manager;

SolarSystemManager manager;

int main(int argc, char* argv[])
{
	//SolarSystem ss;
	//manager = new SolarSystemManager(ss);
	
	// Initialisation de GLUT
	glutInit(&argc, argv);

	// Initialisation de la fenetre
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

	// Creation de la fenetre
	glutCreateWindow("Solar System");
	

	// Initialisation des fonctions de rappel
	glutDisplayFunc(DisplayFunc);
	glutMouseFunc(MouseClickFunc);
	glutMotionFunc(MouseMoveFunc);
	glutKeyboardFunc(KeyboardFunc);

	
	// Initialisation OpenGL
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	// Demarrage du programme
	glutMainLoop();

	//delete manager;
	return 0;
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	manager.KeyboardFunc(key, x, y);
}

void MouseMoveFunc(int x, int y)
{
	manager.MouseMoveFunc(x, y);
}

void MouseClickFunc(int button, int state, int x, int y)
{
	manager.MouseClickFunc(button, state, x, y);
}

void DisplayFunc()
{
	manager.DisplayFunc();
}
