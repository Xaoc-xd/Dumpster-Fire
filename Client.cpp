#include "SDK.h"
#include "Client.h"
#include "Util.h"
#include "Aimbot.h"
#include "Triggerbot.h"
#include "Misc.h"
#include "ChatSpam.h"
#include "AntiAim.h"
#include "RemoveConditions.h"
#include "AutoAirblast.h"

Vector qLASTTICK;

//============================================================================================
bool __fastcall Hooked_CreateMove(PVOID ClientMode, int edx, float input_sample_frametime, CUserCmd* pCommand)
{
	VMTManager& hook = VMTManager::GetHook(ClientMode); //Get a pointer to the instance of your VMTManager with the function GetHook.
	bool bReturn = hook.GetMethod<bool(__thiscall*)(PVOID, float, CUserCmd*)>(gOffsets.iCreateMoveOffset)(ClientMode, input_sample_frametime, pCommand); //Call the original.
	try
	{
		if (!pCommand->command_number)
			return false;

		CBaseEntity* pLocal = GetBaseEntity(me);

		if (!pLocal)
			return bReturn;

		gMisc.Run(pLocal, pCommand);
		gAA.Run(pLocal, pCommand);
		gAim.Run(pLocal, pCommand);
		gCond.Run(pLocal, pCommand);
		gTrigger.Run(pLocal, pCommand);
		gChatSpam.Run(pLocal, pCommand);
		gBlast.Run(pLocal, pCommand);
	}
	catch (...)
	{
		Log::Fatal("Failed Hooked_CreateMove");
	}
	qLASTTICK = pCommand->viewangles;
	return false/*bReturn*/;
}
//============================================================================================
void __fastcall Hooked_FrameStageNotify(void* _this, void* _edx, ClientFrameStage_t stage)
{
	if (gInts.Engine->IsInGame() && stage == FRAME_RENDER_START && gCvars.misc_thirdPerson) //shows antiaims just fine
	{
		CBaseEntity *oEntity = gInts.EntList->GetClientEntity(gInts.Engine->GetLocalPlayer());

		auto *m_angEyeAngles = reinterpret_cast<float*>(reinterpret_cast<DWORD>(oEntity) + gNetVars.get_offset("DT_BasePlayer", "pl", "deadflag") + 8);

		auto *HTC = reinterpret_cast<float*>(reinterpret_cast<DWORD>(oEntity) + gNetVars.get_offset("DT_BasePlayer", "pl", "deadflag") + 4);

		*HTC = qLASTTICK.x;
		*m_angEyeAngles = qLASTTICK.y;

		ConVar* sv_cheats = gInts.cvar->FindVar("sv_cheats");
		if (sv_cheats->GetInt() == 0) sv_cheats->SetValue(1);
		ConVar* pThirdCamYaw = gInts.cvar->FindVar("cam_idealyaw");
		gInts.Engine->ClientCmd_Unrestricted("thirdperson");

		pThirdCamYaw->SetValue(0);
	}
	else if (!gCvars.misc_thirdPerson)
	{
		gInts.Engine->ClientCmd_Unrestricted("firstperson");
	}

	if (gCvars.sky_changer && gInts.Engine->IsInGame())
		if (gInts.cvar->FindVar("sv_skyname")->GetString() != "sky_night_01")
		{
			typedef bool(_cdecl* LoadNamedSkysFn)(const char*);
			static LoadNamedSkysFn LoadSkys = (LoadNamedSkysFn)gSignatures.GetEngineSignature("55 8B EC 81 EC ? ? ? ? 8B 0D ? ? ? ? 53 56 57 8B 01 C7 45");


			if (gCvars.sky_changer) {
				switch ((int)gCvars.sky_changer_value)
				{
				case 1:
					LoadSkys("sky_night_01");
					break;
				case 2:
					LoadSkys("sky_nightfall_01");
					break;
				case 3:
					LoadSkys("sky_harvest_night_01");
					break;
				case 4:
					LoadSkys("sky_halloween");
					break;
				default:
					break;
				}
		}
	}
	for (auto i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		CBaseEntity* pEntity = gInts.EntList->GetClientEntity(i);
		CBaseEntity *entity = nullptr;
		player_info_t pInfo;

		if (!(entity = gInts.EntList->GetClientEntity(i)))
			continue;
		if (entity->IsDormant())
			continue;
		if (!gInts.Engine->GetPlayerInfo(i, &pInfo))
			continue;
		if (!entity->GetLifeState() == LIFE_ALIVE)
			continue;

		if (gCvars.misc_bighead)
		{
			auto *size = reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEntity) + gNetVars.get_offset("DT_TFPlayer", "m_flHeadScale"));
			*size = 7.0f;
		}
		else if (!gCvars.misc_bighead)
		{
			auto *size = reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEntity) + gNetVars.get_offset("DT_TFPlayer", "m_flHeadScale"));
			*size = 1.0f;
		}
	}
	
	auto &hook = VMTManager::GetHook(gInts.Client);
	hook.GetMethod<void(__thiscall *)(PVOID, ClientFrameStage_t)>(35)(gInts.Client, stage);
}
//============================================================================================
int __fastcall Hooked_KeyEvent(PVOID CHLClient, int edx, int eventcode, int keynum, const char *currentBinding)
{
	/*if (eventcode == 1)
	{
		if (keynum == 72) //insert
		{
			gCheatMenu.bMenuActive = !gCheatMenu.bMenuActive;
		}

		if (gCheatMenu.bMenuActive)
		{
			if (keynum == 88 || keynum == 112) // Up
			{

				if (gCheatMenu.iMenuIndex > 0) gCheatMenu.iMenuIndex--;
				else gCheatMenu.iMenuIndex = gCheatMenu.iMenuItems - 1;
				return 0;

			}
			else if (keynum == 90 || keynum == 113) // Down
			{
				if (gCheatMenu.iMenuIndex < gCheatMenu.iMenuItems - 1) gCheatMenu.iMenuIndex++;
				else gCheatMenu.iMenuIndex = 0;
				return 0;

			}
			else if (keynum == 89 || keynum == 107) // Left
			{
				if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value)
				{
					gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] -= gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flStep;
					if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] < gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMin)
						gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] = gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMax;
				}
				return 0;

			}
			else if (keynum == 91 || keynum == 108) // Right
			{
				if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value)
				{
					gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] += gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flStep;
					if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] > gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMax)
						gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] = gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMin;
				}
				return 0;

			}

		}
	}
	*/
	VMTManager &hook = VMTManager::GetHook(CHLClient); // Get a pointer to the instance of your VMTManager with the function GetHook.
	return hook.GetMethod<int(__thiscall *)(PVOID, int, int, const char *)>(gOffsets.iKeyEventOffset)(CHLClient, eventcode, keynum, currentBinding); // Call the original.
}