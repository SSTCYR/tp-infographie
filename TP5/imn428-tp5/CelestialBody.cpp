#define GLUT_DISABLE_ATEXIT_HACK

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif

#define PI							3.14159265358

#include <string>
#include "CelestialBody.h"
#include "BitmapHandling.h"
#include <cmath>
#include <math.h>

typedef struct
{
float x;
float y;
}CIRCLE;

CIRCLE circle;

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, bool hasRing)
{
	m_Radius = radius*MULTIPLIER_EQUAT_RAD;
	m_OrbitRadius = orbitRadius*MULTIPLIER_ORBIT_RAD;
	m_Revolution = revolution*MULTIPLIER_REVOL_PER;
	m_Rotation = rotation*MULTIPLIER_ROTAT_PER;
	m_Position.X = m_OrbitRadius;
	m_Position.Y = 0;
	m_Position.Z = 0;
	m_RotationAngle = 0;
	m_RevolutionAngle = 0;
	m_RotationTime = 0;
	m_RevolutionTime = 0;
	m_PlanetName = planetName;
	m_HasRing = hasRing;
}

CelestialBody::~CelestialBody()
{
}


// TODO : Draw satellite when needed
void CelestialBody::Update(float elapsedTime, Position centerOfRevolution)
{
	m_RevolutionTime += elapsedTime;

	if(m_RevolutionTime > m_Revolution)
	{
		m_RevolutionTime -= m_Revolution;
	}

	m_RevolutionAngle = m_RevolutionTime/m_Revolution*PI*2;

	m_Position.Z = 0*cos(m_RevolutionAngle) - m_OrbitRadius*sin(m_RevolutionAngle);
	m_Position.X = 0*sin(m_RevolutionAngle) + m_OrbitRadius*cos(m_RevolutionAngle);

	m_Position.Z += centerOfRevolution.Z;
	m_Position.X += centerOfRevolution.X;

	m_RotationTime += elapsedTime;

	if(m_RotationTime > m_Rotation)
	{
		m_RotationTime -= m_Rotation;
	}

	m_RotationAngle = (float)m_RotationTime / m_Rotation * 360.0*3;
}

void CelestialBody::DrawOrbit(Position centerOfRevolution)
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 180; i++)
    {
		circle.x = centerOfRevolution.X + (float)m_OrbitRadius *cos((double)i);
		circle.y = centerOfRevolution.Z + (float)m_OrbitRadius *sin((double)i);
		glVertex3f(circle.x,0,circle.y);
		circle.x = centerOfRevolution.X + (float)m_OrbitRadius * cos(i + 0.1);
		circle.y = centerOfRevolution.Z + (float)m_OrbitRadius * sin(i + 0.1);
		glVertex3f(circle.x,0,circle.y);
	
    }
    glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glColor3f(1.0,1.0,1.0);
}


Position CelestialBody::GetPosition() const
{
	return m_Position;
}

float CelestialBody::GetOrbitRadius() const
{
	return m_OrbitRadius;
}

float CelestialBody::GetRadius() const
{
	return m_Radius;
}

float CelestialBody::GetRotation() const
{
	return m_Rotation;
}

float CelestialBody::GetRevolution() const
{
	return m_Revolution;
}

float CelestialBody::GetRotationAngle() const
{
	return m_RotationAngle;
}

float CelestialBody::GetRevolutionAngle() const
{
	return m_RevolutionAngle;
}

char* CelestialBody::GetPlanetName() const
{
	return m_PlanetName;
}

bool CelestialBody::HasRing() const
{
	return m_HasRing;
}