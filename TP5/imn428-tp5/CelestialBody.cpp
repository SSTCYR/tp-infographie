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

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName)
{
	Construct(radius, orbitRadius, revolution, rotation, planetName);
}

CelestialBody::CelestialBody(float radius,	float orbitRadius, float revolution, float rotation, char *planetName, CelestialBody *satellite) : m_Satellite(satellite)
{
	CelestialBody(radius, orbitRadius, revolution, rotation, planetName);
}

CelestialBody::~CelestialBody()
{
}

void CelestialBody::Construct(float radius, float orbitRadius, float revolution, float rotation, char *planetName)
{
	m_Radius = radius*MULTIPLIER_EQUAT_RAD;
	m_OrbitRadius = orbitRadius*MULTIPLIER_ORBIT_RAD;
	m_Revolution = revolution*MULTIPLIER_REVOL_PER;
	m_Rotation = rotation*MULTIPLIER_ROTAT_PER;
	m_Position.X = m_OrbitRadius;
	m_Position.Y = 0;
	m_Position.Z = 0;
	m_Angle = 0;
	m_RotationTime = 0;
	m_PlanetName = planetName;
}

// TODO : Draw satellite when needed
void CelestialBody::Update(float elapsedTime)
{
	float theta = elapsedTime/m_Revolution*PI*2;
	m_Position.Z = m_Position.Z*cos(theta) - m_Position.X*sin(theta);
	m_Position.X = m_Position.Z*sin(theta) + m_Position.X*cos(theta);

	m_RotationTime += elapsedTime;

	if(m_RotationTime > m_Rotation)
	{
		m_RotationTime -= m_Rotation;
	}

	m_Angle = m_RotationTime / m_Rotation * 360.0;
}

//TODO : les bonnes couleurs de lignes
void CelestialBody::DrawOrbit()
{
	float posX, posY, posZ, theta;
	posX = m_OrbitRadius;
	posY = 0;
	posZ = 0;

	glLineWidth(5);
	glColor4f(1,1,1,1);
	glBegin(GL_LINES);
	{
		for(int i = 0; i<3600; i++)
		{
			glVertex3f(posX, posY, posZ);
			posX = m_Position.Z*cos(i/1800*PI) - m_Position.X*sin(i/1800*PI);
			posZ = m_Position.Z*sin(i/1800*PI) + m_Position.X*cos(i/1800*PI);
			glVertex3f(posX, posY, posZ);
		}
	}
	glEnd();
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

float CelestialBody::GetAngle() const
{
	return m_Angle;
}

char* CelestialBody::GetPlanetName() const
{
	return m_PlanetName;
}