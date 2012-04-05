#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(CelestialBody focus) : m_CurrentFocus(focus)
{
}


Camera::~Camera()
{
}

void Camera::ChangeFocus(int planetIndex, bool fixed)
{
}

void Camera::Rotate()
{
}

void Camera::Zoom()
{
}
