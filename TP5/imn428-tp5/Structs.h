#ifndef STRUCTS_H
#define STRUCTS_H

#define GLUT_DISABLE_ATEXIT_HACK

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif

typedef struct
{
	double X;
	double Y;
	double Z;
} Position;

typedef struct 
{
	int button;
	int buttonState;
	int x;
	int y;
} MouseEvent;

typedef struct
{
	GLenum	lightID;
	GLfloat	ambient[4];
	GLfloat	diffuse[4];
	GLfloat	specular[4];
	GLfloat	position[4];

	GLfloat Kc;
	GLfloat Kl;
	GLfloat Kq;

	bool	on;

} Light;

#endif // STRUCTS_H
