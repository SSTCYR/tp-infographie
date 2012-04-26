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
#include "Structs.h"

//Constant used throughout the example
#define PI							3.14159265358

//Functions 

void		InitScene();
void		CleanupScene();
void		IdleCallBack();
void		CreateSolarSystem();

void		RenderScene(float af_DeltaTime);
void		RenderSpinningSphere(float af_DeltaTime, int index);
void		RenderTransparentBillboard(float af_DeltaTime);
void		RenderRing(Ring planetRing);

void		Draw_Skybox(float x, float y, float z, float width, float height, float length);

void		KeyboardFunc(unsigned char key, int x, int y);
void		MouseMoveFunc(int x, int y);
void		MouseClickFunc(int button, int state, int x, int y);
void		SetcurrentKey(int key);
int			GetcurrentKey();

float*		UpdateCameraLookAt();
float*		UpdateCameraFocus();
float*		UpdateCameraPosition(float af_DeltaTime, float revolution);

double		deg2rad( double deg );
double		rad2deg( double rad );


void		setCamera(float af_DeltaTime);

// Variables 

const int	gs32_WindowWidth	= 960;
const int	gs32_WindowHeight	= 600;
const float	gf_FieldofViewY		= 62.7375f;
const float	gf_FarClip			= 800.0f;
const float gf_NearClip			= 0.1f;

const float gf_FrameTime		= 0.015f;

unsigned int gu32_PlanetTexId[11];
unsigned int gu32_BillboardTexId;
unsigned int gu32_Skybox;

float		gtf_LightColor[4]	 = {1.0f, 1.0f, 1.0f, 1.0f};
float		gtf_LightPosition[4] = {0.0f,0.0f,0.0f,1.0f};

float		gtf_PlanetAmbient[4]	= {0.3f, 0.3f, 0.3f, 1.0f};
float		gtf_PlanetDiffuse[4]	= {1.0f, 1.0f, 1.0f, 1.0f};
float		gtf_PlanetEmission[4]	= {0,0,0,0};
float		gtf_PlanetPosition[4]	= {5.0f,0.0f,0.0f, 1.0f};

CelestialBody m_Bodies[11];

Ring		ringSaturn(1.05*MULTIPLIER_EQUAT_RAD*SATURN_EQUATOR_RADIUS, 2*MULTIPLIER_EQUAT_RAD*SATURN_EQUATOR_RADIUS, 0, 6, 0);
Ring		ringUranus(1.2*MULTIPLIER_EQUAT_RAD*URANUS_EQUATOR_RADIUS, 1.6*MULTIPLIER_EQUAT_RAD*URANUS_EQUATOR_RADIUS, 90, 7, 0);

float		gtf_BillboardAmbient[4]		= {0.2f, 0.2f, 0.2f, 0.2f};
float		gtf_BillboardDiffuse[4]		= {1.0f, 1.0f, 1.0f, 1.0f};
float		gtf_BillboardEmission[4]	= {1.0f, 1.0f, 1.0f, 1.0f};
float		gtf_BillboardPosition[4]	= {0.0f,0.0f,0.0f, 1.0f};
float		gf_BillboardHalfSize		= 8;


float		gtf_InitCameraPosition[3]	= {0,10,30};
float		gtf_CameraPosition[3]		= {0,10,30};
float		gtf_FixedCameraPosition[3]	= {0,10,30};

float		revolutionTime = 0;

float		gtf_InitCameraLookAt[3]	= {0,0,0};
float		gtf_CameraLookAt[3]		= {0,0,0};
float		gtf_CameraUp[3]			= {0,1,0};

int			m_currentKey = 0;

static		Timer go_FrameTimer;

boolean		m_Focus = true;

MouseEvent	gLastMouseEvt;			
CamInfo		gCam;

void CreateSolarSystem()
{
	CelestialBody mercury(MERCURY_EQUATOR_RADIUS, MERCURY_ORBIT_RADIUS, MERCURY_REVO_PERIOD, MERCURY_ROTATION_PERIOD, "mercury", false);
	m_Bodies[1] = mercury;
	CelestialBody venus(VENUS_EQUATOR_RADIUS, VENUS_ORBIT_RADIUS, VENUS_REVO_PERIOD, VENUS_ROTATION_PERIOD, "venus", false);
	m_Bodies[2] = venus;
	CelestialBody moon(MOON_EQUATOR_RADIUS, MOON_ORBIT_RADIUS, MOON_REVO_PERIOD, MOON_ROTATION_PERIOD, "moon", false);
	m_Bodies[10] = moon;
	CelestialBody earth(EARTH_EQUATOR_RADIUS, EARTH_ORBIT_RADIUS, EARTH_REVO_PERIOD, EARTH_ROTATION_PERIOD, "earth", false);
	m_Bodies[3] = earth;
	CelestialBody mars(MARS_EQUATOR_RADIUS, MARS_ORBIT_RADIUS, MARS_REVO_PERIOD, MARS_ROTATION_PERIOD, "mars", false);
	m_Bodies[4] = mars;
	CelestialBody jupiter(JUPITER_EQUATOR_RADIUS, JUPITER_ORBIT_RADIUS, JUPITER_REVO_PERIOD, JUPITER_ROTATION_PERIOD, "jupiter", false);
	m_Bodies[5] = jupiter;
	CelestialBody saturn(SATURN_EQUATOR_RADIUS, SATURN_ORBIT_RADIUS, SATURN_REVO_PERIOD, SATURN_ROTATION_PERIOD, "saturn", true);
	m_Bodies[6] = saturn;
	CelestialBody uranus(URANUS_EQUATOR_RADIUS, URANUS_ORBIT_RADIUS, URANUS_REVO_PERIOD/10, URANUS_ROTATION_PERIOD, "uranus", true);
	m_Bodies[7] = uranus;
	CelestialBody neptune(NEPTUNE_EQUATOR_RADIUS, NEPTUNE_ORBIT_RADIUS, NEPTUNE_REVO_PERIOD, NEPTUNE_ROTATION_PERIOD, "neptune", false);
	m_Bodies[8] = neptune;
	CelestialBody pluto(PLUTO_EQUATOR_RADIUS, PLUTO_ORBIT_RADIUS, PLUTO_REVO_PERIOD, PLUTO_ROTATION_PERIOD, "pluto", false);
	m_Bodies[9] = pluto;
	CelestialBody sun(SUN_EQUATOR_RADIUS, SUN_ORBIT_RADIUS, 1, SUN_ROTATION_PERIOD, "sun", false);
	m_Bodies[0] = sun;
}

int main(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_ALPHA|GLUT_DEPTH);
	glutInitWindowSize(gs32_WindowWidth,gs32_WindowHeight);
	glutCreateWindow("Solar system.");

	CreateSolarSystem();

	glutIdleFunc( IdleCallBack );
	glutDisplayFunc(	IdleCallBack );
	glutKeyboardFunc( KeyboardFunc );
	glutMouseFunc( MouseClickFunc );      
    glutMotionFunc( MouseMoveFunc );


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
	char* planetName[11];
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
	planetName[10] = "Resources/texture_moon.bmp";
	char* ringName[2];
	ringName[0] = "Resources/ring_saturn.bmp";
	ringName[1] = "Resources/ring_uranus.bmp";
	
	RGBImage o_TmpTexture;
	for(int i=0;i<11;i++)
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

	//load the skybox's texture in memory	
	LoadBmp("Resources/texture_starbg.bmp",o_TmpTexture);

	glGenTextures(1,&gu32_Skybox);
	glBindTexture(GL_TEXTURE_2D,gu32_Skybox);
	glTexImage2D(GL_TEXTURE_2D,0,3,o_TmpTexture.GetWidth(),o_TmpTexture.GetHeight(),0,GL_RGB,GL_FLOAT,o_TmpTexture.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

	//load ring's texture in memory
	LoadBmp(ringName[0],o_TmpTexture);

	glGenTextures(1,&ringSaturn.ringId);
	glBindTexture(GL_TEXTURE_2D,ringSaturn.ringId);
	glTexImage2D(GL_TEXTURE_2D,0,3,o_TmpTexture.GetWidth(),o_TmpTexture.GetHeight(),0,GL_RGB,GL_FLOAT,o_TmpTexture.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

	LoadBmp(ringName[1],o_TmpTexture);

	glGenTextures(1,&ringUranus.ringId);
	glBindTexture(GL_TEXTURE_2D,ringUranus.ringId);
	glTexImage2D(GL_TEXTURE_2D,0,3,o_TmpTexture.GetWidth(),o_TmpTexture.GetHeight(),0,GL_RGB,GL_FLOAT,o_TmpTexture.GetRasterData());

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering

	gCam.theta= 0.0;
    gCam.phi = 30.0;
    gCam.r = 30.0;

}

void IdleCallBack()
{
	go_FrameTimer.MarkLap();

	if(go_FrameTimer.GetLapTime() >= gf_FrameTime)
	{
		
		RenderScene(go_FrameTimer.GetLapTime());
		go_FrameTimer.ResetTimer();
	}
}


void setCamera(float af_DeltaTime)
{
	if(m_Focus==false)
	{
		float* tab=UpdateCameraLookAt();
		gtf_CameraLookAt[0] = tab[0];
		gtf_CameraLookAt[1] = tab[1];
		gtf_CameraLookAt[2] = tab[2];

	}
	else
	{
		//To do : Faire la vu derrière la caméra. Donc x = Pos.X , y = Revolution de la planète, z = Pos.Z. 
		//Il faut ajouter un cos/sin surêment pour faire tournée la caméra.
		float* tab=UpdateCameraFocus();
		gtf_CameraLookAt[0] = tab[0];
		gtf_CameraLookAt[1] = tab[1];
		gtf_CameraLookAt[2] = tab[2];

		float* pos=UpdateCameraPosition(af_DeltaTime, tab[3]);
		gtf_CameraPosition[0] = pos[0];
		gtf_CameraPosition[1] = pos[1];
		gtf_CameraPosition[2] = pos[2];


	}

	gluLookAt(	gtf_CameraPosition[0],	gtf_CameraPosition[1],	gtf_CameraPosition[2],
				gtf_CameraLookAt[0],	gtf_CameraLookAt[1],	gtf_CameraLookAt[2],
				gtf_CameraUp[0],		gtf_CameraUp[1],		gtf_CameraUp[2]);
	
}

void RenderScene(float af_DeltaTime)
{
	glClearColor(0.0,0.0,0.0,1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Camera Setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(gf_FieldofViewY,gs32_WindowWidth/(float)gs32_WindowHeight,gf_NearClip,gf_FarClip);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	setCamera(af_DeltaTime);
	//Light Setup
	
	glEnable(GL_LIGHT0);

	glLightfv(	GL_LIGHT0,	GL_POSITION,		gtf_LightPosition);
	glLightfv(	GL_LIGHT0,	GL_DIFFUSE,			gtf_LightColor);
	glLightfv(	GL_LIGHT0,	GL_SPECULAR,		gtf_LightColor);
	glLightf(	GL_LIGHT0,	GL_SPOT_CUTOFF,		180.0f);
     
	Draw_Skybox(gtf_CameraPosition[0],gtf_CameraPosition[1],gtf_CameraPosition[2],300.0,300.0,300.0);       

	for(int i=0;i<11;i++) RenderSpinningSphere(af_DeltaTime, i);

	for(int i=1;i<10;i++) m_Bodies[i].DrawOrbit(Position());
	m_Bodies[10].DrawOrbit(m_Bodies[3].GetPosition());

	glutSwapBuffers();
}

void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	//Back
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, gu32_Skybox);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width,y,z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width,y+height,z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z);
	glEnd();
	glPopMatrix();

	//Front
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, gu32_Skybox);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width,y,z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width,y+height,z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z+length);
	glEnd();
	glPopMatrix();

	//Left
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, gu32_Skybox);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y,z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,y+height,z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z);
	glEnd();
	glPopMatrix();

	//Right
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, gu32_Skybox);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width,y,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width,y,z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width,y+height,z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width,y+height,z);
	glEnd();
	glPopMatrix();

	//Up

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, gu32_Skybox);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y+height,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width,y+height,z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width,y+height,z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+height,z+length);
	glEnd();
	glPopMatrix();

	//Down
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, gu32_Skybox);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,y,z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width,y,z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width,y,z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y,z+length);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void RenderSpinningSphere(float af_DeltaTime, int i)
{

	if(i<10) m_Bodies[i].Update(af_DeltaTime, Position());
	else m_Bodies[i].Update(af_DeltaTime, m_Bodies[3].GetPosition());

	if(i==0)
	{
		RenderTransparentBillboard(af_DeltaTime);
		glDisable(GL_LIGHTING);
	}

	glPushMatrix();

		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,gtf_PlanetAmbient);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,gtf_PlanetDiffuse);
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gtf_PlanetEmission);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
		glBindTexture(GL_TEXTURE_2D,gu32_PlanetTexId[i]);

		glTranslatef( m_Bodies[i].GetPosition().X, m_Bodies[i].GetPosition().Y, m_Bodies[i].GetPosition().Z );
		glRotatef( m_Bodies[i].GetRotationAngle() , 0, 1, 0);
		glRotatef( 90,1,0,0);

		GLUquadricObj *po_SphereMesh = gluNewQuadric();

		gluQuadricDrawStyle(po_SphereMesh,GLU_FILL);
		gluQuadricNormals(po_SphereMesh,GLU_SMOOTH);
		gluQuadricTexture(po_SphereMesh,GLU_TRUE);
		gluQuadricOrientation(po_SphereMesh,GLU_OUTSIDE);

		gluSphere(po_SphereMesh,m_Bodies[i].GetRadius(),60,60);

		gluDeleteQuadric(po_SphereMesh);

	glPopMatrix();

	if(m_Bodies[i].HasRing())
	{	
		if (i==ringSaturn.index) RenderRing(ringSaturn);
		else RenderRing(ringUranus);
	}

	if(i==0)
	{
		glEnable(GL_LIGHTING);
	}
}


void RenderTransparentBillboard(float af_DeltaTime)
{
	glDisable(GL_LIGHTING);
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
	glEnable(GL_LIGHTING);
}

//TO DO faire en sorte que l'anneau d'Uranus suive la tangente de son orbite
void RenderRing(Ring planetRing)
{
	glDisable(GL_LIGHTING);
	glPushMatrix();

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,gtf_BillboardAmbient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,gtf_BillboardDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,gtf_BillboardEmission);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
	
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);

		glRotatef( m_Bodies[planetRing.index].GetRevolutionAngle()*180/PI , 0, 1, 0);
		glTranslatef(m_Bodies[planetRing.index].GetOrbitRadius(), 0, 0);
		glRotatef( planetRing.angle , 0, 0, 1);


		float resolution = 30;
		for(int j = 0; j < resolution; j++)
		{
			glBindTexture(GL_TEXTURE_2D,planetRing.ringId);
			glBegin(GL_QUADS);
			{

				glTexCoord2f(0.0f, 1.0f); glVertex3f(planetRing.innerRadius*cos(((float)2*PI/resolution)*j), 0, planetRing.innerRadius*sin(((float)2*PI/resolution)*j));
				glTexCoord2f(1.0f, 1.0f);glVertex3f(planetRing.outerRadius*cos(((float)2*PI/resolution)*j), 0, planetRing.outerRadius*sin(((float)2*PI/resolution)*j));
				glTexCoord2f(1.0f, 0.0f);glVertex3f(planetRing.outerRadius*cos(((float)2*PI/resolution)*(j+1)), 0, planetRing.outerRadius*sin(((float)2*PI/resolution)*(j+1)));
				glTexCoord2f(0.0f, 0.0f);glVertex3f(planetRing.innerRadius*cos(((float)2*PI/resolution)*(j+1)), 0, planetRing.innerRadius*sin(((float)2*PI/resolution)*(j+1)));
			}
			glEnd();
		}

	glDisable (GL_BLEND);
	glDepthMask(GL_TRUE);

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

/* Camera Function */ 

void KeyboardFunc(unsigned char key, int x, int y)
{
	
switch (key)
  {
	case '0':  
		if(m_currentKey == 0)
		{
			SetcurrentKey(0);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			SetcurrentKey(0);
			m_Focus = true;
			revolutionTime = 0;
			gtf_FixedCameraPosition[0] = gtf_InitCameraPosition[0];
			gtf_FixedCameraPosition[1] = gtf_InitCameraPosition[1];
			gtf_FixedCameraPosition[2] = gtf_InitCameraPosition[2];
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '1':   
		if(m_currentKey == 1)
		{
			printf("Follow mercury\n");
			SetcurrentKey(1);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			printf("Focus on mercury\n");
			SetcurrentKey(1);
			m_Focus = true;
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '2':   
		if(m_currentKey == 2)
		{
			printf("Follow venus\n");
			SetcurrentKey(2);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());			
		}
		else
		{
			printf("Focus on venus\n");
			SetcurrentKey(2);
			m_Focus = true;
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '3':   
		if(m_currentKey == 3)
		{
			printf("Follow earth\n");
			SetcurrentKey(3);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			printf("Focus on earth\n");
			SetcurrentKey(3);
			m_Focus = true;
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '4':   
		if(m_currentKey == 4)
		{
			printf("Follow mars\n");
			SetcurrentKey(4);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			printf("Focus on mars\n");
			m_Focus = true;
			SetcurrentKey(4);
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '5':   
		if(m_currentKey == 5)
		{
			printf("Follow jupiter\n");
			SetcurrentKey(5);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			printf("Focus on jupiter\n");
			SetcurrentKey(5);
			m_Focus = true;
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '6':   
		if(m_currentKey == 6)
		{
			printf("Follow saturn\n");
			SetcurrentKey(6);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			printf("Focus on saturn\n");
			SetcurrentKey(6);
			m_Focus = true;
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '7':   
		if(m_currentKey == 7)
		{
			printf("Follow uranus\n");
			SetcurrentKey(7);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			printf("Focus on uranus\n");
			SetcurrentKey(7);
			m_Focus = true;
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '8':   
		if(m_currentKey == 8)
		{
			printf("Follow neptune\n");
			SetcurrentKey(8);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			printf("Focus on neptune\n");
			SetcurrentKey(8);
			m_Focus = true;
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	case '9':   
		if(m_currentKey == 9)
		{
			printf("Follow pluto\n");
			SetcurrentKey(9);
			m_Focus = false;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		else
		{
			printf("Focus on pluto\n");
			SetcurrentKey(9);
			m_Focus = true;
			revolutionTime = 0;
			RenderScene(go_FrameTimer.GetLapTime());
		}
		break;
	
  }
  
}

void MouseClickFunc(int button, int state, int x, int y)
{
	if(m_Focus == true)
	{
		if( state == GLUT_DOWN )
		{
			gLastMouseEvt.button = button;
			gLastMouseEvt.x = x;
			gLastMouseEvt.y = y;
		}
		else
		if( state == GLUT_UP )
		{
			gLastMouseEvt.button = -1;
			gLastMouseEvt.x = -1;
			gLastMouseEvt.y = -1;
		}
	}
}



void MouseMoveFunc(int x, int y)
{
	if(m_Focus == true)
	{
		int	dx = x - gLastMouseEvt.x;
		int	dy = -y + gLastMouseEvt.y;
		float m[16];
		gLastMouseEvt.x = x;
		gLastMouseEvt.y = y;

		switch( gLastMouseEvt.button )
		{
			case GLUT_LEFT_BUTTON:
			{
				/* Rotation */
				gCam.theta -= dx;
				gCam.phi   -= dy;
				if( gCam.phi >  89 ) gCam.phi =  89;
				if( gCam.phi < -89 ) gCam.phi = -89;

				 
				gtf_FixedCameraPosition[0] = gCam.r*sin(deg2rad(gCam.theta))*cos(deg2rad(gCam.phi));
				gtf_FixedCameraPosition[1] = gCam.r*sin(deg2rad(gCam.phi));
				gtf_FixedCameraPosition[2] = gCam.r*cos(deg2rad(gCam.theta))*cos(deg2rad(gCam.phi));


				break;
			}
			case GLUT_RIGHT_BUTTON:
			{
				/* Zoom in/out */
				gCam.r += dx - dy;
				if( gCam.r < 1 )	gCam.r = 1;

				gtf_FixedCameraPosition[0] = gCam.r*sin(deg2rad(gCam.theta))*cos(deg2rad(gCam.phi));
				gtf_FixedCameraPosition[1] = gCam.r*sin(deg2rad(gCam.phi));
				gtf_FixedCameraPosition[2] = gCam.r*cos(deg2rad(gCam.theta))*cos(deg2rad(gCam.phi));

				break;
			}
			default:
				return;
		}

		setCamera(go_FrameTimer.GetLapTime());
		//RenderScene(go_FrameTimer.GetLapTime()); // Move the camera.
		//glutPostRedisplay();
	}
}

float* UpdateCameraLookAt()
{
	float* pointer;
	float info[3];

	pointer = info;

	if (m_currentKey == 0)
	{
		info[0] = 0; 
		info[1] = 0; 
		info[2] = 0; 
	}
	else
	{
		info[0] = m_Bodies[m_currentKey].GetPosition().X; 
		info[1] = m_Bodies[m_currentKey].GetPosition().Y;
		info[2] = m_Bodies[m_currentKey].GetPosition().Z; 
	}

	return pointer;
}

float* UpdateCameraFocus()
{
	float* pointer;
	float info[4];

	pointer = info;

	if (m_currentKey == 0)
	{
		info[0] = 0; 
		info[1] = 0; 
		info[2] = 0; 
		info[3] = 0; 
	}
	else
	{
		info[0] = m_Bodies[m_currentKey].GetPosition().X; 
		info[1] = m_Bodies[m_currentKey].GetPosition().Y;
		info[2] = m_Bodies[m_currentKey].GetPosition().Z; 
		info[3] = m_Bodies[m_currentKey].GetRevolution(); 
	}

	return pointer;
}

float* UpdateCameraPosition(float af_DeltaTime, float revolution)
{
	float* pointer;
	float info[3];

	/*if (m_currentKey == 0)
	{
		pointer = gtf_InitCameraPosition;
	}
	
	
	else
	{	*/
		/*gtf_FixedCameraPosition[0] = gtf_FixedCameraPosition[0]*sin(deg2rad(gCam.theta))*cos(deg2rad(gCam.phi));
		gtf_FixedCameraPosition[1] = gtf_FixedCameraPosition[1]*sin(deg2rad(gCam.phi));
		gtf_FixedCameraPosition[2] = gtf_FixedCameraPosition[2]*cos(deg2rad(gCam.theta))*cos(deg2rad(gCam.phi));*/



		float X = gtf_FixedCameraPosition[0]+m_Bodies[m_currentKey].GetOrbitRadius();
		float Z = gtf_FixedCameraPosition[2];

		info[2] = (Z)*cos(m_Bodies[m_currentKey].GetRevolutionAngle()) - (X)*sin(m_Bodies[m_currentKey].GetRevolutionAngle());
		info[1] = gtf_FixedCameraPosition[1];
		info[0] = (Z)*sin(m_Bodies[m_currentKey].GetRevolutionAngle()) + (X)*cos(m_Bodies[m_currentKey].GetRevolutionAngle());

		pointer = info;

	//}

	return pointer;
}

/* Get/Set function */



void SetcurrentKey(int key)
{
	m_currentKey = key;
}

int GetcurrentKey()
{
	return m_currentKey;
}

double deg2rad( double deg )
{
	return	0.01745329251994329547437168059786927187815 * deg;
}

double rad2deg( double rad )
{
	return	57.2957795130823228646477218717336654663085 * rad;
}