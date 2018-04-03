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

	CBaseEntity* pEntity = GetBaseEntity(GetBestTarget(pLocal));

	if (!pEntity)
		return;

	int iBestHitbox = GetBestHitbox(pLocal, pEntity);

	if (iBestHitbox == -1)
		return;

	Vector vEntity = pEntity->GetHitboxPosition(iBestHitbox);

	Vector vLocal = pLocal->GetEyePosition();

	Vector vAngs, dAngs, sAngs;
	VectorAngles((vEntity - vLocal), vAngs);

	ClampAngle(vAngs);
	gCvars.iAimbotIndex = pEntity->GetIndex();

	if (gCvars.aimbot_smooth) // Thanks to gir489 for coding and Castle for sharing
	{
		unsigned int smoothValue = gCvars.aimbot_smooth_amt;
		Vector lAngs = gInts.Engine->GetViewAngles();

		dAngs = vAngs - lAngs;
		ClampAngle(dAngs);

		sAngs = lAngs + dAngs / 100.f * smoothValue;
		ClampAngle(sAngs);

		pCommand->viewangles = sAngs;
		gInts.Engine->SetViewAngles(pCommand->viewangles);
	}

	else
	{
		if (gCvars.aimbot_silent)
		{
			MovementFix(pCommand, vAngs);
			pCommand->viewangles = vAngs; // Nothing fancy, just client-sided.
		}

		else
		{
			pCommand->viewangles = vAngs;
			gInts.Engine->SetViewAngles(pCommand->viewangles);
		}
	}

	if (gCvars.aimbot_autoshoot)
	{
		if (pLocal->GetCond() & TFCond_Zoomed && !Util->IsReadyToHeadshot(pLocal->GetActiveWeapon()))
			return;

		pCommand->buttons |= IN_ATTACK;
	}
}

float CAimbot::AngleDifference(Vector ViewAngles, Vector TargetAngles, float Distance)
{
	float pitch = sin(DEG2RAD(ViewAngles.x - TargetAngles.x)) * Distance;
	float yaw = sin(DEG2RAD(ViewAngles.y - TargetAngles.y)) * Distance;

	return sqrt(powf(pitch, 2.0) + powf(yaw, 2.0));
}

int CAimbot::GetBestTarget(CBaseEntity* pLocal)
{
	int iBestTarget = -1;

	float flDistToBest = 8192.f;

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

		Vector vEntity = pEntity->GetHitboxPosition(iBestHitbox);

		if (!gCvars.PlayerMode[i])
			continue;

		if (pEntity->GetCond() & TFCond_Ubercharged ||
			pEntity->GetCond() & TFCond_UberchargeFading ||
			pEntity->GetCond() & TFCond_Bonked)
			continue;

		if (gCvars.aimbot_ignore_cloak && pEntity->GetCond() & TFCond_Cloaked)
			continue;

		Vector vAngs;
		VectorAngles((vEntity - vLocal), vAngs);

		ClampAngle(vAngs);

		float flDistToTarget = AngleDifference(gInts.Engine->GetViewAngles(), vAngs, 180);

		if (flDistToTarget > gCvars.aimbot_fov)
			continue;

		if (flDistToTarget < flDistToBest)
		{
			flDistToBest = flDistToTarget;
			iBestTarget = i;
		}

		if (gCvars.PlayerMode[i] == 2) // Rage targets are the first priorities
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
		return -1;

	return iBestHitbox;
}

void CAimbot::MovementFix(CUserCmd *cmd, Vector angles) // Thanks to F1ssi0N for coding and plasma for sharing
{
	Vector vecSilent(cmd->forwardmove, cmd->sidemove, cmd->upmove);
	float flSpeed = sqrt(vecSilent.x * vecSilent.x + vecSilent.y * vecSilent.y);

	Vector angMove;
	VectorAngles(vecSilent, angMove);

	float flYaw = DEG2RAD(angles.y - cmd->viewangles.y + angMove.y);

	cmd->forwardmove = cos(flYaw) * flSpeed;
	cmd->sidemove = sin(flYaw) * flSpeed;
}