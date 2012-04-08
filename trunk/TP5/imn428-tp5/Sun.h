#ifndef SUN_H
#define SUN_H

#include "CelestialBody.h"

class Sun : public CelestialBody
{
private:
	RGBImage m_Billboard;
	unsigned int m_BillboardId;
protected:
	void Draw(Position centerOfRevolution);
	void Construct(float radius, float orbitRadius, float rotation, char *planetName);
public:
	Sun();
	Sun(float radius, float orbitRadius, float rotation, char *planetName);
	~Sun();
};

#endif // SUN_H
