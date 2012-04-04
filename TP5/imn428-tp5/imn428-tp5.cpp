#define GLUT_DISABLE_ATEXIT_HACK

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif

#include "SolarSystem.h"

int main(int argc, char* argv[])
{
	SolarSystem ss;
	ss.RenderScene();
	return 0;
}

