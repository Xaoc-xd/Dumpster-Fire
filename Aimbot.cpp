#include "Aimbot.h"
#include "Util.h"

CAimbot gAim;

void CAimbot::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	gCvars.iAimbotIndex = -1;

	if (!gCvars.aimbot_active)
		return;

	if (!Util->IsKeyPressed(gCvars.aimbot_key))
		return;

	if (!pLocal->GetActiveWeapon())
		return;

	if (gCvars.aimbot_zoomedonly &&
		pLocal->GetClassNum() == TF2_Sniper &&
		Util->IsHeadshotWeapon(pLocal, pLocal->GetActiveWeapon()) &&
		!(pLocal->GetCond() & TFCond_Zoomed))
		return;

	Vector finalAngles = gInts.Engine->GetViewAngles();
	Vector clientAngles = finalAngles;
	float lowestDist = 180;

	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		if (i == me)
			continue;
		CBaseEntity* pEntity = GetBaseEntity(i);
		if (pEntity == NULL || pEntity->IsDormant())
			continue;

		// Deciding if we should aim or not
		if (pEntity->GetLifeState() != LIFE_ALIVE ||
			pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;

		if (!gCvars.PlayerMode[i])
			continue;

		if (pEntity->GetCond() & TFCond_Ubercharged ||
			pEntity->GetCond() & TFCond_UberchargeFading ||
			pEntity->GetCond() & TFCond_Bonked)
			continue;

		if (gCvars.aimbot_ignore_cloak && pEntity->GetCond() & TFCond_Cloaked)
			continue;

		int hitbox = GetBestHitbox(pLocal, pEntity);
		Vector start = pLocal->GetEyePosition(), targetPos = pEntity->GetHitboxPosition(hitbox);
		if (!canHit(pLocal, pEntity, start, targetPos)) // vischecking
			continue;
		Vector direction = targetPos - start; // A line in the direction of our target

		Vector angles; // Converting that line direction to angles
		VectorAngles(direction, angles);
		ClampAngle(angles); // Making sure it stays within TF2's angle range

		// Get the distance of the target from our crosshair
		Vector angleDiff = angles - clientAngles;
		float ydist = angleDiff.y;

		// The max degrees between two points on a circle is 180 if you want the shortest path
		if (ydist > 180)
			ydist -= 360;
		else if (ydist < -180)
			ydist += 360;

		// Check to see if it's outside of our FOV range
		angleDiff = Vector(abs(ydist), abs(angleDiff.x), 0);
		// Pythagoream theorem best theorem
		float trueDist = sqrt(pow(angleDiff.x, 2) + pow(angleDiff.y, 2));
		if (trueDist > gCvars.aimbot_fov)
			continue;

		// Check for lower FOV distance than last target
		if (trueDist < lowestDist)
			gCvars.iAimbotIndex = i, lowestDist = trueDist, finalAngles = angles;
	}
	if (gCvars.aimbot_silent)
		Util->silentMovementFix(pCommand, finalAngles);
	if (gCvars.aimbot_smooth)
	{
		Vector smoothedAngle;
		SmoothAngle(pCommand->viewangles, finalAngles, smoothedAngle, gCvars.aimbot_smooth_amt);
		pCommand->viewangles = smoothedAngle;
		gInts.Engine->SetViewAngles(smoothedAngle);
	}
	else
	{
		pCommand->viewangles = finalAngles;

		if (!gCvars.aimbot_silent)
			gInts.Engine->SetViewAngles(pCommand->viewangles);
	}

	if (gCvars.aimbot_autoshoot && gCvars.iAimbotIndex != -1) {
		if (pLocal->GetCond() & TFCond_Zoomed && !Util->IsReadyToHeadshot(pLocal->GetActiveWeapon()))
			return;

		pCommand->buttons |= IN_ATTACK;
	}
}



/*void CAimbot::silentMovementFix(CUserCmd *pUserCmd, Vector angles)
{
	Vector vecSilent(pUserCmd->forwardmove, pUserCmd->sidemove, pUserCmd->upmove);
	float flSpeed = sqrt(vecSilent.x * vecSilent.x + vecSilent.y * vecSilent.y);
	Vector angMove;
	VectorAngles(vecSilent, angMove);
	float flYaw = DEG2RAD(angles.y - pUserCmd->viewangles.y + angMove.y);
	pUserCmd->forwardmove = cos(flYaw) * flSpeed;
	pUserCmd->sidemove = sin(flYaw) * flSpeed;
}
sorry bro but im doing this my way <3*/
bool CAimbot::canHit(void* you, void* target, Vector vStart, Vector vEnd/*, trace_t *result*/)
{
	trace_t Trace;
	Ray_t Ray;
	CTraceFilter Filter;

	Filter.pSkip = you;

	Ray.Init(vStart, vEnd);
	gInts.EngineTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

	//if (result != nullptr)
	//  result[0] = Trace;

	return (Trace.m_pEnt == target);
}
void CAimbot::SmoothAngle(Vector& currentAngle, Vector& aimAngle, Vector& smoothedAngle, float fSmoothPercentage)
{
	ClampAngle(aimAngle);
	smoothedAngle = aimAngle - currentAngle;
	smoothedAngle = currentAngle + smoothedAngle / 100.f * fSmoothPercentage;
	ClampAngle(smoothedAngle);
}

int CAimbot::GetBestTarget(CBaseEntity* pLocal)
{
	int iBestTarget = -1;
						 //this num could be smaller 
	float flDistToBest = 99999.f;

	Vector vLocal = pLocal->GetEyePosition();

	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		if (i == me)
			continue;

		CBaseEntity* pEntity = GetBaseEntity(i);

		if (!pEntity)

			continue;

		if (pEntity->IsDormant())
			continue;

		if (pEntity->GetLifeState() != LIFE_ALIVE ||
			pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;

		int iBestHitbox = GetBestHitbox(pLocal, pEntity);

		if (iBestHitbox == -1)
			continue;

		Vector vEntity = pEntity->GetHitboxPosition(iBestHitbox); //pEntity->GetWorldSpaceCenter(vEntity);

		if (!gCvars.PlayerMode[i])
			continue;

		if (pEntity->GetCond() & TFCond_Ubercharged ||
			pEntity->GetCond() & TFCond_UberchargeFading ||
			pEntity->GetCond() & TFCond_Bonked)
			continue;

		float flDistToTarget = (vLocal - vEntity).Length();

		if (flDistToTarget < flDistToBest)
		{
			flDistToBest = flDistToTarget;
			iBestTarget = i;
		}

		if (gCvars.PlayerMode[i] == 2) //always aim at rage targets first
			return i;
	}

	return iBestTarget;
}

int CAimbot::GetBestHitbox(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
	int iBestHitbox = -1;

	if (!gCvars.aimbot_hitbox)
	{
		if (Util->IsHeadshotWeapon(pLocal, pLocal->GetActiveWeapon()))
			iBestHitbox = 0;
		else
			iBestHitbox = 4;
	}
	else
	{
		iBestHitbox = gCvars.aimbot_hitbox - 1;
	}

	if (gCvars.aimbot_hitscan)
	{
		for (int i = 0; i < 17; i++)
		{
			if (Util->IsVisible(pLocal, pEntity, pLocal->GetEyePosition(), pEntity->GetHitboxPosition(i)))
				return i;
		}
	}

	if (pEntity->GetHitboxPosition(iBestHitbox).IsZero())
		return -1;

	if (!Util->IsVisible(pLocal, pEntity, pLocal->GetEyePosition(), pEntity->GetHitboxPosition(iBestHitbox)))
		return - 1;
	
	return iBestHitbox;
}