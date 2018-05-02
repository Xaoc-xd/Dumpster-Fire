#pragma once
#include "SDK.h"

class CAimbot
{
public:

	void Run(CBaseEntity* pLocal, CUserCmd* pCommand);

	float AngleDifference(Vector ViewAngles, Vector TargetAngles, float Distance);

	void MovementFix(CUserCmd *cmd, Vector angles);

	float GetFOV(Vector angle, Vector src, Vector dst);

private:

	int GetBestTarget(CBaseEntity* pLocal, CUserCmd* pCommand);

	int GetBestHitbox(CBaseEntity* pLocal, CBaseEntity* pEntity);

	void MakeVector(Vector angle, Vector & vector);

	Vector calc_angle(Vector src, Vector dst);
};

extern CAimbot gAim;