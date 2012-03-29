#define GLUT_DISABLE_ATEXIT_HACK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif

int main(int argc, char* argv[])
{
	return 0;
}

