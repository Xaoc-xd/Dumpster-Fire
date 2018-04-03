#pragma once
#include "SDK.h"

class CAimbot
{
public:

	void Run(CBaseEntity* pLocal, CUserCmd* pCommand);

	float AngleDifference(Vector ViewAngles, Vector TargetAngles, float Distance);

	void MovementFix(CUserCmd *cmd, Vector angles);

private:

	int GetBestTarget(CBaseEntity* pLocal);

	int GetBestHitbox(CBaseEntity* pLocal, CBaseEntity* pEntity);
};

extern CAimbot gAim;