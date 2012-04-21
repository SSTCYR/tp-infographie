#include "SolarSystem.h"
#include "SolarSystemManager.h"
#include <vector>

#include "RGBImage.h"
#include "BitmapHandling.h"

using namespace std;

void KeyboardFunc(unsigned char key, int x, int y);
void MouseMoveFunc(int x, int y);
void MouseClickFunc(int button, int state, int x, int y);
void DisplayFunc();

SolarSystemManager manager;

int main(int argc, char* argv[])
{
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

	/*-----------------------------------------------------*/
	GLuint penis=0;
	RGBImage text;
	LoadBmp("Resources/texture_earth.bmp", text);
	
	glGenTextures(1, &penis);

	glBindTexture(GL_TEXTURE_2D, penis);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, text.GetWidth(), text.GetHeight(), 0, GL_RGB, GL_FLOAT, text.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	float		gtf_PlanetAmbient[4]	= {0.3f, 0.3f, 0.3f, 1.0f};
	float		gtf_PlanetDiffuse[4]	= {1.0f, 1.0f, 1.0f, 1.0f};
	float		gtf_PlanetEmission[4]	= {0,0,0,0};

	glPushMatrix();


		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,gtf_PlanetAmbient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,gtf_PlanetDiffuse);
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gtf_PlanetEmission);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
		glBindTexture(GL_TEXTURE_2D, penis);

		glTranslatef(10, 0, 0);
		
		GLUquadricObj *po_SphereMesh = gluNewQuadric();

		gluQuadricDrawStyle(po_SphereMesh,GLU_FILL);
		gluQuadricNormals(po_SphereMesh,GLU_SMOOTH);
		gluQuadricTexture(po_SphereMesh,GLU_FALSE);
		gluQuadricOrientation(po_SphereMesh,GLU_OUTSIDE);

		
		gluSphere(po_SphereMesh,10,60,60);
		
		gluDeleteQuadric(po_SphereMesh);

	glPopMatrix();
	/*--------------------------------------------------------------*/

	//manager.CreateSolarSystem();

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
