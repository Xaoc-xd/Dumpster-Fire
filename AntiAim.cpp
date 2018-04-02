#include "AntiAim.h"
#include "Util.h"

CAA gAA;

void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
	float deltaView;
	float f1;
	float f2;

	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;

	if (pCmd->viewangles.y < 0.0f)
		f2 = 360.0f + pCmd->viewangles.y;
	else
		f2 = pCmd->viewangles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);

	deltaView = 360.0f - deltaView;

	pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}

void CAA::Run(CBaseEntity * pLocal, CUserCmd * pCommand)
{
	Vector angles = pCommand->viewangles;
	if (!gCvars.aa_switch)
		return;

	if ((pCommand->buttons & IN_ATTACK) || (pCommand->buttons & IN_ATTACK2))
		return;
	if (gCvars.aa_pitch_fakeup)
	{
		angles.x = -271;
	}
	if (gCvars.aa_pitch_fakedown)
	{
		angles.x = 271;
	}
	if (gCvars.aa_yaw_right)
	{
		angles.y = 90;
	}
	if (gCvars.aa_yaw_left)
	{
		angles.y = -90;
	}

	if (gCvars.aa_yaw_staticjitter)
	{

		int random = rand() % 100;

		if (random < 98)
			angles.y -= 180;

		if (random < 15)
		{
			float change = -70 + (rand() % (int)(140 + 1));
			angles.y += change;
		}
		if (random == 69)
		{
			float change = -90 + (rand() % (int)(180 + 1));
			angles.y += change;
		}
	}
	Util->SilentMovementFix(pCommand, angles);
	pCommand->viewangles = angles;
}

