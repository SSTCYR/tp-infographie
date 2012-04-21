#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Glut/GLUT.h"
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#include "SolarSystemTimer.h"
#include "RGBImage.h"
#include "BitmapHandling.h"
#include "SolarSystem_Config.h"
#include "CelestialBody.h"
#include "Sun.h"
#include "RingPlanet.h"

//Constant used throughout the example
#define PI							3.14159265358

void		InitScene();
void		CleanupScene();
void		IdleCallBack();
void		CreateSolarSystem();

void		RenderScene(float af_DeltaTime);
void		RenderSpinningSphere(float af_DeltaTime, int index);
void		RenderTransparentBillboard(float af_DeltaTime);

const int	gs32_WindowWidth	= 960;
const int	gs32_WindowHeight	= 600;
const float	gf_FieldofViewY		= 62.7375f;
const float	gf_FarClip			= 200.0f;
const float gf_NearClip			= 0.1f;

const float gf_FrameTime		= 0.015f;

unsigned int gu32_PlanetTexId[10];
unsigned int gu32_BillboardTexId;

float		gtf_LightColor[4]	 = {1.0f, 1.0f, 1.0f, 1.0f};
float		gtf_LightPosition[4] = {0.0f,0.0f,0.0f,1.0f};

float		gtf_PlanetAmbient[4]	= {0.3f, 0.3f, 0.3f, 1.0f};
float		gtf_PlanetDiffuse[4]	= {1.0f, 1.0f, 1.0f, 1.0f};
float		gtf_PlanetEmission[4]	= {0,0,0,0};
float		gtf_PlanetPosition[4]	= {5.0f,0.0f,0.0f, 1.0f};

CelestialBody m_Bodies[10];

float		gtf_BillboardAmbient[4] = {0.2f, 0.2f, 0.2f, 0.2f};
float		gtf_BillboardDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float		gtf_BillboardEmission[4] = {1.0f, 1.0f, 1.0f, 1.0f};
float		gtf_BillboardPosition[4]= {0.0f,0.0f,0.0f, 1.0f};
float		gf_BillboardHalfSize = 8;

float		gtf_CameraPosition[3]	= {0,0,30};
float		gtf_CameraLookAt[3]		= {0,0,0};
float		gtf_CameraUp[3]			= {0,1,0};

void CreateSolarSystem()
{
	CelestialBody mercury(MERCURY_EQUATOR_RADIUS, MERCURY_ORBIT_RADIUS, MERCURY_REVO_PERIOD, MERCURY_ROTATION_PERIOD, "mercury");
	m_Bodies[1] = mercury;
	CelestialBody venus(VENUS_EQUATOR_RADIUS, VENUS_ORBIT_RADIUS, VENUS_REVO_PERIOD, VENUS_ROTATION_PERIOD, "venus");
	m_Bodies[2] = venus;
	CelestialBody moon(MOON_EQUATOR_RADIUS, MOON_ORBIT_RADIUS, MOON_REVO_PERIOD, MOON_ROTATION_PERIOD, "moon");
	CelestialBody earth(EARTH_EQUATOR_RADIUS, EARTH_ORBIT_RADIUS, EARTH_REVO_PERIOD, EARTH_ROTATION_PERIOD, "earth", &moon);
	m_Bodies[3] = earth;
	CelestialBody mars(MARS_EQUATOR_RADIUS, MARS_ORBIT_RADIUS, MARS_REVO_PERIOD, MARS_ROTATION_PERIOD, "mars");
	m_Bodies[4] = mars;
	CelestialBody jupiter(JUPITER_EQUATOR_RADIUS, JUPITER_ORBIT_RADIUS, JUPITER_REVO_PERIOD, JUPITER_ROTATION_PERIOD, "jupiter");
	m_Bodies[5] = jupiter;
	RingPlanet saturn(SATURN_EQUATOR_RADIUS, SATURN_ORBIT_RADIUS, SATURN_REVO_PERIOD, SATURN_ROTATION_PERIOD, "saturn");
	m_Bodies[6] = saturn;
	RingPlanet uranus(URANUS_EQUATOR_RADIUS, URANUS_ORBIT_RADIUS, URANUS_REVO_PERIOD, URANUS_ROTATION_PERIOD, "uranus");
	m_Bodies[7] = uranus;
	CelestialBody neptune(NEPTUNE_EQUATOR_RADIUS, NEPTUNE_ORBIT_RADIUS, NEPTUNE_REVO_PERIOD, NEPTUNE_ROTATION_PERIOD, "neptune");
	m_Bodies[8] = neptune;
	CelestialBody pluto(PLUTO_EQUATOR_RADIUS, PLUTO_ORBIT_RADIUS, PLUTO_REVO_PERIOD, PLUTO_ROTATION_PERIOD, "pluto");
	m_Bodies[9] = pluto;
	Sun sun(SUN_EQUATOR_RADIUS, SUN_ORBIT_RADIUS, SUN_ROTATION_PERIOD, "sun");
	m_Bodies[0] = sun;
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_ALPHA|GLUT_DEPTH);
	glutInitWindowSize(gs32_WindowWidth,gs32_WindowHeight);
	glutCreateWindow("Very simple example of what you need to create your project.");

	CreateSolarSystem();

	glutIdleFunc( IdleCallBack );
	glutDisplayFunc(	IdleCallBack );

	InitScene();
	glutMainLoop();
}

void InitScene()
{
	//Setup OpenGL's generic states.
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

	//Load the planet's texture in memory. 
	//Take note that the actual image is created on the stack. It will be destroyed
	//when the function exits, as we don't need the image anymore once it's in video
	//memory.
	char* planetName[10];
	planetName[0] = "Resources/texture_sun.bmp";
	planetName[1] = "Resources/texture_mercury.bmp";
	planetName[2] = "Resources/texture_venus.bmp";
	planetName[3] = "Resources/texture_earth.bmp";
	planetName[4] = "Resources/texture_mars.bmp";
	planetName[5] = "Resources/texture_jupiter.bmp";
	planetName[6] = "Resources/texture_saturn.bmp";
	planetName[7] = "Resources/texture_uranus.bmp";
	planetName[8] = "Resources/texture_neptune.bmp";
	planetName[9] = "Resources/texture_pluto.bmp";
	
	RGBImage o_TmpTexture;
	for(int i=0;i<10;i++)
	{
		LoadBmp(planetName[i],o_TmpTexture);

		glGenTextures(1,&gu32_PlanetTexId[i]);
		glBindTexture(GL_TEXTURE_2D,gu32_PlanetTexId[i]);
		glTexImage2D(GL_TEXTURE_2D,0,3,o_TmpTexture.GetWidth(),o_TmpTexture.GetHeight(),0,GL_RGB,GL_FLOAT,o_TmpTexture.GetRasterData());

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
	}

	//Load the billboard's texture in memory. 
	LoadBmp("Resources/billboard_sun.bmp",o_TmpTexture);

	glGenTextures(1,&gu32_BillboardTexId);
	glBindTexture(GL_TEXTURE_2D,gu32_BillboardTexId);
	glTexImage2D(GL_TEXTURE_2D,0,3,o_TmpTexture.GetWidth(),o_TmpTexture.GetHeight(),0,GL_RGB,GL_FLOAT,o_TmpTexture.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
}

void IdleCallBack()
{
	static Timer go_FrameTimer;

	go_FrameTimer.MarkLap();

	if(go_FrameTimer.GetLapTime() >= gf_FrameTime)
	{
		RenderScene(go_FrameTimer.GetLapTime());
		go_FrameTimer.ResetTimer();
	}
}

void RenderScene(float af_DeltaTime)
{
	glClearColor(0.0,0.0,0.0,1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Camera setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(gf_FieldofViewY,gs32_WindowWidth/(float)gs32_WindowHeight,gf_NearClip,gf_FarClip);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(	gtf_CameraPosition[0],	gtf_CameraPosition[1],	gtf_CameraPosition[2],
				gtf_CameraLookAt[0],	gtf_CameraLookAt[1],	gtf_CameraLookAt[2],
				gtf_CameraUp[0],		gtf_CameraUp[1],		gtf_CameraUp[2]);

	//Light Setup
	
	glEnable(GL_LIGHT0);

	glLightfv(	GL_LIGHT0,	GL_POSITION,		gtf_LightPosition);
	glLightfv(	GL_LIGHT0,	GL_DIFFUSE,			gtf_LightColor);
	glLightfv(	GL_LIGHT0,	GL_SPECULAR,		gtf_LightColor);
	glLightf(	GL_LIGHT0,	GL_SPOT_CUTOFF,		180.0f);
	
	
	for(int i=1;i<10;i++) m_Bodies[i].DrawOrbit();
	for(int i=0;i<10;i++) RenderSpinningSphere(af_DeltaTime, i);
	RenderTransparentBillboard(af_DeltaTime);

	glutSwapBuffers();
}

void RenderSpinningSphere(float af_DeltaTime, int i)
{
	m_Bodies[i].Update(af_DeltaTime);
	
	if(i==0)
	{
		glDisable(GL_LIGHTING);
	}

	glPushMatrix();

		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,gtf_PlanetAmbient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,gtf_PlanetDiffuse);
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gtf_PlanetEmission);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
		glBindTexture(GL_TEXTURE_2D,gu32_PlanetTexId[i]);

		glTranslatef( m_Bodies[i].GetPosition().X, m_Bodies[i].GetPosition().Y, m_Bodies[i].GetPosition().Z );
		glRotatef( m_Bodies[i].GetAngle() , 0, 1, 0);
		glRotatef( 90,1,0,0);

		GLUquadricObj *po_SphereMesh = gluNewQuadric();

		gluQuadricDrawStyle(po_SphereMesh,GLU_FILL);
		gluQuadricNormals(po_SphereMesh,GLU_SMOOTH);
		gluQuadricTexture(po_SphereMesh,GLU_TRUE);
		gluQuadricOrientation(po_SphereMesh,GLU_OUTSIDE);

		gluSphere(po_SphereMesh,m_Bodies[i].GetRadius(),60,60);

		gluDeleteQuadric(po_SphereMesh);

	glPopMatrix();

	if(i==0)
	{
		glEnable(GL_LIGHTING);
	}
}

void RenderTransparentBillboard(float af_DeltaTime)
{
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,gtf_BillboardAmbient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,gtf_BillboardDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gtf_BillboardEmission);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
	glBindTexture(GL_TEXTURE_2D,gu32_BillboardTexId);

	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);

	glPushMatrix();

		float f_TmpModelViewMat[16];
		
		glGetFloatv(GL_MODELVIEW_MATRIX,f_TmpModelViewMat);

		f_TmpModelViewMat[0] = 1;
		f_TmpModelViewMat[1] = 0;
		f_TmpModelViewMat[2] = 0;

		f_TmpModelViewMat[4] = 0;
		f_TmpModelViewMat[5] = 1;
		f_TmpModelViewMat[6] = 0;

		f_TmpModelViewMat[8] = 0;
		f_TmpModelViewMat[9] = 0;
		f_TmpModelViewMat[10] = 1;

		glLoadMatrixf(f_TmpModelViewMat);

		glTranslatef(gtf_BillboardPosition[0],gtf_BillboardPosition[1],gtf_BillboardPosition[2]);

		glBegin(GL_QUADS);

			glTexCoord2d(0,0);
			glVertex3f(-gf_BillboardHalfSize,-gf_BillboardHalfSize,0);

			glTexCoord2d(1,0);
			glVertex3f(gf_BillboardHalfSize,-gf_BillboardHalfSize,0);

			glTexCoord2d(1,1);
			glVertex3f(gf_BillboardHalfSize,gf_BillboardHalfSize,0);

			glTexCoord2d(0,1);
			glVertex3f(-gf_BillboardHalfSize,gf_BillboardHalfSize,0);

		glEnd();

	glPopMatrix();

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);

}