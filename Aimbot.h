#pragma once
#include "SDK.h"

class CAimbot
{
public:

	void Run(CBaseEntity* pLocal, CUserCmd* pCommand);

	//void silentMovementFix(CUserCmd * pUserCmd, Vector angles);

private:

	int GetBestTarget(CBaseEntity* pLocal);

	int GetBestHitbox(CBaseEntity* pLocal, CBaseEntity* pEntity);

	bool canHit(void* you, void* target, Vector vStart, Vector vEnd/*, trace_t *result*/);
	void SmoothAngle(Vector& currentAngle, Vector& aimAngle, Vector& smoothedAngle, float fSmoothPercentage);
};

extern CAimbot gAim; //dsajkhfdlksahf