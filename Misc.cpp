#include "Misc.h"
#include "Util.h"

CMisc gMisc;

void CMisc::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	//if (gInts.cvar->FindVar("viewmodel_fov")->GetInt != gCvars.misc_viewmodel_fov)
	gInts.cvar->FindVar("viewmodel_fov")->SetValue(gCvars.misc_viewmodel_fov);
	pLocal->setfov(gCvars.misc_fov);

	if (!(pLocal->GetFlags() & FL_ONGROUND) && pCommand->buttons & IN_JUMP)
	{
		if (gCvars.misc_autostrafe)
			if (pCommand->mousedx > 1 || pCommand->mousedx < -1)  //> 1 < -1 so we have some wiggle room
				pCommand->sidemove = pCommand->mousedx > 1 ? 450.f : -450.f;

		if (gCvars.misc_bunnyhop)
			pCommand->buttons &= ~IN_JUMP;
	}

	if (gCvars.misc_autobackstab)
	{
		if (pLocal->GetActiveWeapon() && Util->IsReadyToBackstab(pLocal, pLocal->GetActiveWeapon()))
			pCommand->buttons |= IN_ATTACK;
	}

	if (gCvars.misc_noisemaker_spam)
	{
		PVOID kv = Util->InitKeyValue();
		if (kv != NULL)
		{
			NoisemakerSpam(kv);
			gInts.Engine->ServerCmdKeyValues(kv);
		}
	}

	if (gCvars.misc_thirdPerson)
	{
		pLocal->ForceTauntCam(true);
	}
	else
	{
		pLocal->ForceTauntCam(false);
	}
	
	if (gCvars.misc_roll_speedhack && !(pCommand->buttons & IN_ATTACK)) // I have to improve this later on.
	{
		Vector vLocalAngles = pCommand->viewangles;
		float speed = pCommand->forwardmove;
		if (fabs(speed) > 0.0f) {
			pCommand->forwardmove = -speed;
			pCommand->sidemove = 0.0f;
			pCommand->viewangles.y = vLocalAngles.y;
			pCommand->viewangles.y -= 180.0f;
			if (pCommand->viewangles.y < -180.0f) pCommand->viewangles.y += 360.0f;
			pCommand->viewangles.z = 90.0f;
		}
	}

	if (gCvars.misc_wowsweet && fLastTime + 0.5f < gInts.globals->curtime)
	{
		if (pLocal->szGetClass() == "Heavy" && pLocal->GetActiveWeapon() && pLocal->GetActiveWeapon()->GetSlot() == 1 && pLocal->GetFlags() & FL_DUCKING)
		{
			if (pCommand->tick_count % 2)
				gInts.Engine->ClientCmd_Unrestricted("say wow sweet");
			else
				gInts.Engine->ClientCmd_Unrestricted("say wow sweet\x0D");
			fLastTime = gInts.globals->curtime;
		}
	}

	if (gCvars.misc_voiceCheers)
	{
		gInts.Engine->ClientCmd_Unrestricted("voicemenu 2 2");
	}
	if (gCvars.misc_voiceJeers)
	{
		gInts.Engine->ClientCmd_Unrestricted("voicemenu 2 3");
	}
	if (gCvars.misc_voiceNiceShot)
	{
		gInts.Engine->ClientCmd_Unrestricted("voicemenu 2 6");
	}
	if (gCvars.misc_voiceDispenser)
	{
		gInts.Engine->ClientCmd_Unrestricted("voicemenu 1 4");
	}
	if (gCvars.misc_voiceActivateCharge)
	{
		gInts.Engine->ClientCmd_Unrestricted("voicemenu 1 6");
	}
	if (gCvars.misc_voiceMedic)
	{
		gInts.Engine->ClientCmd_Unrestricted("voicemenu 0 0");
	}
	if (gCvars.misc_voiceThanks)
	{
		gInts.Engine->ClientCmd_Unrestricted("voicemenu 0 1");
	}
}

void CMisc::NoisemakerSpam(PVOID kv) //Credits gir https://www.unknowncheats.me/forum/team-fortress-2-a/141108-infinite-noisemakers.html
{
	char chCommand[30] = "use_action_slot_item_server";
	typedef int(__cdecl* HashFunc_t)(const char*, bool);
	static DWORD dwHashFunctionLocation = gSignatures.GetClientSignature("FF 15 ? ? ? ? 83 C4 08 89 06 8B C6");
	static HashFunc_t s_pfGetSymbolForString = (HashFunc_t)**(PDWORD*)(dwHashFunctionLocation + 0x2);
	*(PDWORD)((DWORD)kv + 0x4) = 0;
	*(PDWORD)((DWORD)kv + 0x8) = 0;
	*(PDWORD)((DWORD)kv + 0xC) = 0;
	*(PDWORD)((DWORD)kv + 0x10) = 0xDEADBEEF;
	*(PDWORD)((DWORD)kv + 0x14) = 0;
	*(PDWORD)((DWORD)kv + 0x18) = 0;
	*(PDWORD)((DWORD)kv + 0x1C) = 0;
	*(PDWORD)((DWORD)kv + 0) = s_pfGetSymbolForString(chCommand, 1);
}