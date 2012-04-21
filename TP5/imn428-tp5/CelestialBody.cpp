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
	m_Position.X = 0;
	m_Position.Y = 0;
	m_Position.Z = 0;
	m_PlanetName = planetName;
	/*
	char textureName[30];
	strcpy(textureName, "Resources/texture_");
	strcat(textureName, planetName);
	strcat(textureName, ".bmp");

	LoadBmp(textureName, m_Texture);

	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, m_Texture.GetWidth(), m_Texture.GetHeight(), 0, GL_RGB, GL_FLOAT, m_Texture.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	*/
}

// TODO : Add some sciency magic to update its position and camera position
void CelestialBody::Update(float elapsedTime, unsigned int textId)
{
	Draw(Position(), textId);
}

// TODO : Add revolution and rotation movement
// TODO : Add ring
// TODO : Add billboard for the sun
// TODO : Draw satellite when needed
void CelestialBody::Draw(Position centerOfRevolution, unsigned int textId)
{
	float		gtf_PlanetAmbient[4]	= {0.3f, 0.3f, 0.3f, 1.0f};
	float		gtf_PlanetDiffuse[4]	= {1.0f, 1.0f, 1.0f, 1.0f};
	float		gtf_PlanetEmission[4]	= {0,0,0,0};

	glPushMatrix();


		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,gtf_PlanetAmbient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,gtf_PlanetDiffuse);
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gtf_PlanetEmission);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
		glBindTexture(GL_TEXTURE_2D, textId);

		glTranslatef(m_OrbitRadius, 0, 0);
		
		GLUquadricObj *po_SphereMesh = gluNewQuadric();

		gluQuadricDrawStyle(po_SphereMesh,GLU_FILL);
		gluQuadricNormals(po_SphereMesh,GLU_SMOOTH);
		gluQuadricTexture(po_SphereMesh,GLU_FALSE);
		gluQuadricOrientation(po_SphereMesh,GLU_OUTSIDE);

		
		gluSphere(po_SphereMesh,m_Radius,60,60);
		
		gluDeleteQuadric(po_SphereMesh);

	glPopMatrix();
}

Position CelestialBody::GetPosition() const
{
	return m_Position;
}

float CelestialBody::GetOrbitRadius() const
{
	return m_OrbitRadius;
}

char* CelestialBody::GetPlanetName() const
{
	return m_PlanetName;
}