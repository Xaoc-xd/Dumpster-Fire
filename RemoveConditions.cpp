#include "RemoveConditions.h"

RemoveCondExploits gCond;

void RemoveCondExploits::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{
	if (!gCvars.removecond_enabled)
		return;

	if (Util->IsKeyPressed(gCvars.removecond_key) //G
											   //  && pLocal->GetLifeState() == LIFE_ALIVE
		&& !gInts.Engine->Con_IsVisible()
		&& gInts.Engine->IsConnected())
		RemoveConds(pLocal, pCommand, gCvars.removecond_value);

	if (gCvars.removecond_autoinstantcap)
	{
		for (int i = 1; i < gInts.EntList->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* pEnt = GetBaseEntity(i);

			if (!pEnt) continue;

			if (pEnt->GetTeamNum() == pLocal->GetTeamNum()) continue;

			if (!strcmp(pEnt->GetModelName(), "models/props_gameplay/cap_point_base.mdl"))
			{
				Vector entPos = pEnt->GetEyePosition();
				Vector localPos = pLocal->GetEyePosition();
				float distance = Util->flGetDistance(localPos, entPos);
				if (distance < 22.0 && Util->IsVisible(pLocal, pEnt, localPos, entPos))
				{
					gCond.RemoveConds(pLocal, gCvars.removecond_value);
				}
			}
		}
	}

	if (gCvars.removecond_instantweaponswitch)
	{
		static int lastweapon = 0;
		if (lastweapon != pCommand->weaponselect)
			RemoveConds(pLocal, pCommand, gCvars.removecond_value, false);
		lastweapon = pCommand->weaponselect;
	}

	if (gCvars.removecond_automedkit)
	{
		for (int i = 1; i <= gInts.EntList->GetHighestEntityIndex(); i++)
		{
			CBaseEntity *pEnt = gInts.EntList->GetClientEntity(i);
			if (!pEnt)
				continue;

			if (pEnt->GetOwner() != -1) continue; // We cant insta medkit dropped ammo/health packs

			const char* pszModelName = pEnt->GetModelName();
			if (!strcmp(pszModelName, "models/items/medkit_small.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_small_bday.mdl")
				|| !strcmp(pszModelName, "models/props_halloween/halloween_medkit_small.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_medium.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_medium_bday.mdl")
				|| !strcmp(pszModelName, "models/props_halloween/halloween_medkit_medium.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_large.mdl")
				|| !strcmp(pszModelName, "models/items/medkit_large_bday.mdl")
				|| !strcmp(pszModelName, "models/props_halloween/halloween_medkit_large.mdl")
				&& pLocal->GetHealth() < pLocal->GetMaxHealth())
			{

				Vector entPos;
				pEnt->GetWorldSpaceCenter(entPos);
				Vector eyePos = pLocal->GetEyePosition();

				float dist = Util->flGetDistance(entPos, eyePos);

				if (dist < 9.5)
				{
					RemoveConds(pLocal, pCommand, gCvars.removecond_value);
				}

			}
			if (!strcmp(pszModelName, "models/items/ammopack_small.mdl")
				|| !strcmp(pszModelName, "models/items/ammopack_small_bday.mdl")
				|| !strcmp(pszModelName, "models/items/ammopack_medium.mdl")
				|| !strcmp(pszModelName, "models/items/ammopack_medium_bday.mdl"))
			{
				Vector entPos;
				pEnt->GetWorldSpaceCenter(entPos);
				Vector eyePos = pLocal->GetEyePosition();

				float dist = Util->flGetDistance(entPos, eyePos);

				if (dist < 9.5)
				{
					RemoveConds(pLocal, pCommand, gCvars.removecond_value);
				}
			}
		}
	}
}
void RemoveCondExploits::RemoveConds(CBaseEntity * local, CUserCmd * cmd, int value, bool disableattack)
{
	if (local == NULL) return;

	/*if(!cmd) return;
	if(!cmd->command_number) return;*/
	//if(!var.value) return;

	if (local->GetLifeState() != LIFE_ALIVE) return;

	if (disableattack)
		if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2) return;

	INetChannel* ch = (INetChannel*)gInts.Engine->GetNetChannelInfo();
	int& m_nOutSequenceNr = *(int*)((unsigned)ch + 8);
	m_nOutSequenceNr += value;
}

void RemoveCondExploits::RemoveConds(CBaseEntity *local, int value)
{
	RemoveConds(local, new CUserCmd(), value);
}