#include "Helper.h"
#include "VektoriaMath\Util.h"

CHelper::CHelper()
{
}


CHelper::~CHelper()
{
}

float CHelper::AngleToRad(float fAngle)
{
	return (2.0f * PI * fAngle) / 360.0f;
}

float CHelper::RadToAngle(float fRadiant)
{
	return (360.0f * fRadiant) / TWOPI;
}
