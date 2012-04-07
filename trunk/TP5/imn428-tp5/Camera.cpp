#include "Camera.h"

Camera *Camera::m_Instance = 0;

Camera::Camera()
{
}

Camera::~Camera()
{
	delete m_Instance;
}

Camera *Camera::GetInstance()
{
	if(!m_Instance)
		m_Instance = new Camera();
	return m_Instance;
}

void Camera::ChangeFocus(int planetIndex, bool fixed)
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
