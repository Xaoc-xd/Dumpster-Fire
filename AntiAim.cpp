#include "AntiAim.h"
#include "Util.h"

CAA gAA;
float c_yaw = 0.0f;

void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove) //you guys know that the aa movement fix is the same as silent movement fix, right? :thinking:
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

	if (!gCvars.aa_enabled)
		return;

	if ((pCommand->buttons & IN_ATTACK) || (pCommand->buttons & IN_ATTACK2))
		return;

	if (gCvars.aa_pitch_enabled) {
		switch ((int)gCvars.aa_pitch)
		{
		case 1://Fake up
			angles.x = -271.0;
			break;
		case 2://Up
			angles.x = -89.0f;
			break;
		case 3://Fake down
			angles.x = 271.0;
			break;
		case 4://Down
			angles.x = 89.0f;
			break;
		default:
			break;
		}
	}

	if (gCvars.aa_yaw_enabled) {
		switch ((int)gCvars.aa_yaw)
		{
		case 1://Right
			angles.y -= 90.0f;
			break;
		case 2://Left
			angles.y += 90.0f;
			break;
		case 3://Back
			angles.y -= 180;
			break;
		case 4://Random
			angles.y = Util->RandFloatRange(-180.0f, 180.0f);
			break;
		case 5://Spin
			c_yaw += gCvars.aa_spinspeed;
			if (c_yaw > 180) c_yaw = -180;
			if (c_yaw < -180) c_yaw = 180;
			angles.y = c_yaw;
			break;
		default:
			break;
		}
	}
	Util->SilentMovementFix(pCommand, angles);
	pCommand->viewangles = angles;
}

