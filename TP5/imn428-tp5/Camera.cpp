#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

/* Camera::LookAtUpdate(CelestialBody m_currentCelestialBody)
{

	gluLookAt(	0,10,50,
				m_currentCelestialBody.GetPosition().X,	m_currentCelestialBody.GetPosition().Y,	m_currentCelestialBody.GetPosition().Z,
				0,1,0);

}*/

void Camera::Rotate(int x, int y)
{
	m_Theta -= x;
	m_Phi -= y;

	if( m_Phi >  89 ) 
		m_Phi =  89;

	if( m_Phi < -89 ) 
		m_Phi = -89;
}

void Camera::Zoom(int distance)
{
	m_Distance += distance;
	if(m_Distance < 1)
		m_Distance = 1;
}
