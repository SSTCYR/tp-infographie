#ifndef SUN_H
#define SUN_H

#include "CelestialBody.h"

class Sun : public CelestialBody
{
protected:
	void Construct(float radius, float orbitRadius, float rotation, char *planetName);
public:
	Sun();
	Sun(float radius, float orbitRadius, float rotation, char *planetName);
	~Sun();
	void Update(float elapsedTime);
};

#endif // SUN_H
