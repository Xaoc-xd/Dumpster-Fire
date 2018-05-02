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

	CBaseEntity* pEntity = GetBaseEntity(GetBestTarget(pLocal, pCommand));

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

int CAimbot::GetBestTarget(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	int iBestTarget = -1;

	float flDistToBest = 8192.f;

	Vector vLocal = pLocal->GetEyePosition();
	float minimalDistance = 99999.0;

	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		if (i == me)
			continue;

		CBaseEntity* pEntity = GetBaseEntity(i);

		auto pWep = pLocal->GetActiveWeapon();
		auto pClass = pWep->GetItemDefinitionIndex();


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

		if (gCvars.PlayerMode[i] == 2)
			return i;

		auto demo = pClass == demomanweapons::WPN_Sword || pClass == demomanweapons::WPN_FestiveEyelander || pClass == demomanweapons::WPN_Golfclub || pClass == demomanweapons::WPN_ScottsSkullctter || pClass == demomanweapons::WPN_Headless;
		if (pWep->GetSlot() == 2 && !demo)
			minimalDistance = (float)8.4;

		if (pClass == demomanweapons::WPN_Sword || pClass == demomanweapons::WPN_FestiveEyelander || pClass == demomanweapons::WPN_Golfclub || pClass == demomanweapons::WPN_ScottsSkullctter || pClass == demomanweapons::WPN_Headless)
			minimalDistance = 12.0;

		if (pLocal->szGetClass() == "Pyro" && (pClass == pyroweapons::WPN_Backburner || pClass == pyroweapons::WPN_Degreaser || pClass == pyroweapons::WPN_FestiveBackburner || pClass == pyroweapons::WPN_FestiveFlamethrower || pClass == pyroweapons::WPN_Flamethrower || pClass == pyroweapons::WPN_Phlogistinator || pClass == pyroweapons::WPN_Rainblower || pClass == pyroweapons::WPN_NostromoNapalmer))
			minimalDistance = 17.0;

		float flFOV = GetFOV(pCommand->viewangles, vLocal, vEntity);
		float distance = Util->flGetDistance(vEntity, pLocal->GetEyePosition());

		if (distance < minimalDistance)
		{
			if (flFOV < flDistToBest && flFOV < gCvars.aimbot_fov)
			{
				if (gCvars.PlayerMode[i] == 2)
					return i;
				flDistToBest = flFOV;
				gCvars.iAimbotIndex = i;
				iBestTarget = i;
			}
		}
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

Vector CAimbot::calc_angle(Vector src, Vector dst)
{
	Vector AimAngles, delta;
	float hyp;
	delta = src - dst;
	hyp = sqrtf((delta.x * delta.x) + (delta.y * delta.y));
	AimAngles.x = atanf(delta.z / hyp) * RADPI;
	AimAngles.y = atanf(delta.y / delta.x) * RADPI;
	AimAngles.z = 0.0f;
	if (delta.x >= 0.0)
		AimAngles.y += 180.0f;
	return AimAngles;
}

void CAimbot::MakeVector(Vector angle, Vector& vector)
{
	float pitch, yaw, tmp;
	pitch = float(angle[0] * PI / 180);
	yaw = float(angle[1] * PI / 180);
	tmp = float(cos(pitch));
	vector[0] = float(-tmp * -cos(yaw));
	vector[1] = float(sin(yaw)*tmp);
	vector[2] = float(-sin(pitch));
}

float CAimbot::GetFOV(Vector angle, Vector src, Vector dst)
{
	Vector ang, aim;
	float mag, u_dot_v;
	ang = calc_angle(src, dst);


	MakeVector(angle, aim);
	MakeVector(ang, ang);

	mag = sqrtf(pow(aim.x, 2) + pow(aim.y, 2) + pow(aim.z, 2));
	u_dot_v = aim.Dot(ang);

	return RAD2DEG(acos(u_dot_v / (pow(mag, 2))));
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