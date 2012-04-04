#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include <vector>

#include "RGBImage.h"
#include "SolarSystemTimer.h"
#include "Utility.h"

using std::vector;

struct CBParam
{
	float radius;
	float orbitRadius;
	float revolution;
	float rotation;

	CBParam(float rad, float oRad, float rev, float rot) : 
	radius(rad), orbitRadius(oRad), revolution(rev), rotation(rot) {}
};

class CelestialBody
{
private:
	bool m_IsSun;
	bool m_HasRing;
	Position m_Position;
	RGBImage m_Texture;
	RGBImage m_Ring;
	Timer m_Timer;

	void InitRing();
public:
	CelestialBody(CBParam param, char *planetName, bool isSun, Timer& timer, vector<CelestialBody> satellites);
	CelestialBody(CBParam param, char *planetName, Timer& timer, bool hasRing);
	~CelestialBody();  
	Position GetPosition();
	vector<CelestialBody> GetSatellites();
	void Update();
};

#endif // CELESTIAL_BODY_H
