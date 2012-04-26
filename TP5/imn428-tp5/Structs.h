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

struct Position
{
	double X;
	double Y;
	double Z;

	Position() : X(0), Y(0), Z(0) { }
};

typedef struct
{
	int	button;  /* left, middle, right */
	int stateButton; /* pressed or not */
	int	x;
	int	y;
} MouseEvent;

typedef struct
{
	GLfloat	theta;	/* angle de rotation sur le plane X/Z */
	GLfloat	phi;	/* angle d'elevation du plan X/Z */
	GLfloat	r;		/* distance d'eloignement */
	GLfloat fovy;   /* angle d'ouverture */
	GLfloat ratio;  /* ration hauteur/largeur de la fenetre courante */
	GLfloat znear;   /* near clipping plane */
	GLfloat zfar;    /* far clipping plane */
} CamInfo;

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

struct Ring
{
	float			innerRadius;
	float			outerRadius;
	float			angle;
	int				index;
	unsigned int	ringId;
	Ring(float inR, float ouR, float ang, int i, unsigned int id) : innerRadius(inR), outerRadius(ouR), angle(ang), index(i), ringId(id) {}
};

#endif // STRUCTS_H
