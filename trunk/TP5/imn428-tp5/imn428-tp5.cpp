#include "SolarSystem.h"
#include "SolarSystemManager.h"

void KeyboardFunc(unsigned char key, int x, int y);
void MouseMoveFunc(int x, int y);
void MouseClickFunc(int button, int state, int x, int y);
void DisplayFunc();

SolarSystemManager *manager;

int main(int argc, char* argv[])
{
	SolarSystem ss;
	manager = new SolarSystemManager(ss);

	// Initialisation de GLUT
	glutInit(&argc, argv);

	// Initialisation de la fenetre
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// Creation de la fenetre
	glutCreateWindow("Solar System");
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

	// Initialisation des fonctions de rappel
	glutDisplayFunc(DisplayFunc);
	glutMouseFunc(MouseClickFunc);
	glutMotionFunc(MouseMoveFunc);
	glutKeyboardFunc(KeyboardFunc);

	// Initialisation de la camera

	// Demarrage du programme
	glutMainLoop();

	delete manager;
	return 0;
}

void KeyboardFunc(unsigned char key, int x, int y)
{
	manager->KeyboardFunc(key, x, y);
}

void MouseMoveFunc(int x, int y)
{
	manager->MouseMoveFunc(x, y);
}

void MouseClickFunc(int button, int state, int x, int y)
{
	manager->MouseClickFunc(button, state, x, y);
}

void DisplayFunc()
{
	manager->DisplayFunc();
}
