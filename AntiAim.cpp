#include "AntiAim.h"
#include "Util.h"

CAA gAA;

void CAA::Run(CBaseEntity * pLocal, CUserCmd * pCommand)
{
	if (gCvars.aa_pitch_fakeup)
	{

		if (pCommand->buttons & IN_ATTACK)
			return;

		pCommand->viewangles.x = -271;
	}
	if (gCvars.aa_pitch_fakedown)
	{

		if (pCommand->buttons & IN_ATTACK)
			return;

		pCommand->viewangles.x = 271;
	}
	if (gCvars.aa_yaw_right)
	{

		if (pCommand->buttons & IN_ATTACK)
			return;

		pCommand->viewangles.y = 90;
	}
	if (gCvars.aa_yaw_left)
	{

		if (pCommand->buttons & IN_ATTACK)
			return;
		pCommand->viewangles.y = -90;
	}
}
