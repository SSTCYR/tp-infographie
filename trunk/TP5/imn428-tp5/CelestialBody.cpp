#include "CelestialBody.h"

CelestialBody::CelestialBody()
{
}

CelestialBody::CelestialBody(CBParam param, char *planetName, bool isSun, Timer& timer, vector<CelestialBody> satellites)
{
}

CelestialBody::CelestialBody(CBParam param, char *planetName, Timer& timer, bool hasRing)
{
}

CelestialBody::~CelestialBody()
{
}

void CelestialBody::InitRing()
{
}

Position CelestialBody::GetPosition()
{
}

vector<CelestialBody> CelestialBody::GetSatellites()
{
}

void CelestialBody::Update()
{
}