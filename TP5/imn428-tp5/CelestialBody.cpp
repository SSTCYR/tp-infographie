#define GLUT_DISABLE_ATEXIT_HACK

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif

#include <string>
#include "CelestialBody.h"
#include "BitmapHandling.h"

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName)
{
	Construct(radius, orbitRadius, revolution, rotation, planetName);
	
		LoadBmp(strcat(strcat("Resources/ring_", planetName), ".bmp"), m_Ring);
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, CelestialBody *satellite) : m_Satellite(satellite)
{
	CelestialBody(radius, orbitRadius, revolution, rotation, planetName, false);
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float rotation, char *planetName) :
m_Radius(radius), m_OrbitRadius(orbitRadius), m_Rotation(rotation)
{
	LoadBmp(strcat(strcat("Resources/billboard_", planetName), ".bmp"), m_Billboard);
}

CelestialBody::~CelestialBody()
{
}

void CelestialBody::Construct(float radius, float orbitRadius, float revolution, float rotation, char *planetName)
{
	m_Radius = radius;
	m_OrbitRadius = orbitRadius;
	m_Revolution = revolution;
	m_Rotation = rotation;
	m_Position.X = 0;
	m_Position.Y = 0;
	m_Position.Z = 0;

	LoadBmp(strcat(strcat("Resources/texture_", planetName), ".bmp"), m_Texture);
}

// TODO : Add some sciency magic to update its position and camera position
void CelestialBody::Update(float elapsedTime)
{
	Draw(Position());
}

// TODO : Add revolution and rotation movement
// TODO : Add ring
// TODO : Add billboard for the sun
// TODO : Draw satellite when needed
void CelestialBody::Draw(Position centerOfRevolution)
{
	glPushMatrix();

		glTranslatef(m_Radius, 0, 0);

		GLUquadricObj *po_SphereMesh = gluNewQuadric();

		gluQuadricDrawStyle(po_SphereMesh,GLU_FILL);
		gluQuadricNormals(po_SphereMesh,GLU_SMOOTH);
		gluQuadricTexture(po_SphereMesh,GLU_FALSE);
		gluQuadricOrientation(po_SphereMesh,GLU_OUTSIDE);

		gluSphere(po_SphereMesh,m_Radius,60,60);

		gluDeleteQuadric(po_SphereMesh);

	glPopMatrix();
}

inline Position CelestialBody::GetPosition() const
{
	return m_Position;
}

inline float CelestialBody::GetOrbitRadius() const
{
	return m_OrbitRadius;
}
