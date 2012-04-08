#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

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
