
// Look if this class is important to keep
/*#define GLUT_DISABLE_ATEXIT_HACK

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include "Glut/GLUT.h"
#endif
#include "SolarSystemManager.h"
#include "BitmapHandling.h"
#include "CelestialBody.h"
SolarSystemManager Key;

float		gtf_CameraPosition[3]	= {0,10,50};
float		gtf_CameraLookAt[3]		= {0,0,0};
float		gtf_CameraUp[3]			= {0,1,0};

SolarSystemManager::SolarSystemManager()
{
	m_currentKey = 0;

}

void SolarSystemManager::KeyboardFunc(unsigned char key, int x, int y)
{
	
switch (key)
  {
	case '0':  
		if(Key.m_currentKey == (int)key)
		{
			printf("Already on sun!\n");
		}
		else
		{
			printf("The sun!\n");
		}
		SetcurrentKey((int)key);
		break;
		
		// Sun
	case '1':   
		if(Key.m_currentKey == (int)key)
		{
			
			gluLookAt(	gtf_CameraPosition[0],	gtf_CameraPosition[1],	gtf_CameraPosition[2],
						gtf_CameraLookAt[0],	gtf_CameraLookAt[1],	gtf_CameraLookAt[2],
						gtf_CameraUp[0],		gtf_CameraUp[1],		gtf_CameraUp[2]);
		}
		else
		{
			printf("Focus on mercury\n");
		}
		SetcurrentKey((int)key);
		break;
	case '2':   
		if(Key.m_currentKey == (int)key)
		{
			printf("Follow venus\n");
		}
		else
		{
			printf("Focus on venus\n");
		}
		SetcurrentKey((int)key);
		break;
	case '3':   
		if(Key.m_currentKey == (int)key)
		{
			printf("Follow earth\n");
		}
		else
		{
			printf("Focus on earth\n");
		}
		SetcurrentKey((int)key);
		break;
	case '4':   
		if(Key.m_currentKey == (int)key)
		{
			printf("Follow mars\n");
		}
		else
		{
			printf("Focus on mars\n");
		}
		SetcurrentKey((int)key);
		break;
	case '5':   
		if(Key.m_currentKey == (int)key)
		{
			printf("Follow jupiter\n");
		}
		else
		{
			printf("Focus on jupiter\n");
		}
		SetcurrentKey((int)key);
		break;
	case '6':   
		if(Key.m_currentKey == (int)key)
		{
			printf("Follow saturn\n");
		}
		else
		{
			printf("Focus on saturn\n");
		}
		SetcurrentKey((int)key);
		break;
	case '7':   
		if(Key.m_currentKey == (int)key)
		{
			printf("Follow uranus\n");
		}
		else
		{
			printf("Focus on uranus\n");
		}
		SetcurrentKey((int)key);
		break;
	case '8':   
		if(Key.m_currentKey == (int)key)
		{
			printf("Follow neptune\n");
		}
		else
		{
			printf("Focus on neptune\n");
		}
		SetcurrentKey((int)key);
		break;
	case '9':   
		if(Key.m_currentKey == (int)key)
		{
			printf("Follow pluto\n");
		}
		else
		{
			printf("Focus on pluto\n");
		}
		SetcurrentKey((int)key);
		break;
	
  }
}

void SolarSystemManager::MouseClickFunc(int button, int state, int x, int y)
{
	switch(button)
	{
		case (GLUT_LEFT_BUTTON):
		{
			if(state == GLUT_DOWN)
			{
			}
			break;
		}
		case (GLUT_MIDDLE_BUTTON):
		{
			if(state == GLUT_DOWN)
			{
			}
			break;
		}
		case (GLUT_RIGHT_BUTTON):
		{
			break;
		}
		default:
		{
			if(state == GLUT_DOWN)
			{
			}
			break;
		}

		glutPostRedisplay();
	}
}

void SolarSystemManager::MouseMoveFunc(int x, int y)
{
}

void SolarSystemManager::SetcurrentKey(int key)
{
	Key.m_currentKey = key;
}

int SolarSystemManager::GetcurrentKey()
{
	return SolarSystemManager::m_currentKey;
}
*/
