#include "KillSay.h"

CKillSay gKillSay;


void CKillSay::InitKillSay()
{
	gInts.EventManager->AddListener(this, "player_death", false);
	wasEventInitialized = true;
}

void CKillSay::FireGameEvent(IGameEvent *event)
{

	if (!strcmp(event->GetName(), "player_death") && gCvars.misc_killsay_selection > 0)
	{
		int vid = event->GetInt("userid");
		int kid = event->GetInt("attacker");
		if (kid == vid) return;
		if (gInts.Engine->GetPlayerForUserID(kid) != gInts.Engine->GetLocalPlayer()) return;

		const std::vector<std::string>* source = nullptr;
		std::string msg;
		msg.append("say ");

		// Can't use a float in an if statement because it is not an integral type

		if (gCvars.misc_killsay_selection == 1)
			source = &KillSay::niggerhook;
		else if (gCvars.misc_killsay_selection == 2)
			source = &KillSay::ncc;
		else
			source = &killsayFile.lines;

		/*switch (gCvars.misc_killsay_selection)
		{
		case 1:
			source = &KillSay::niggerhook;
			break;
		case 2:
			source = &KillSay::ncc;
			break;
		case 3:
			source = &killsayFile.lines;
			break;
		}

		if (gCvars.killsay.newlines)//\x0D
		{
			msg.append(" ");
			msg.append(repeat(gCvars.killsay.newlines, "\x0D"));
		}*/
		msg.append(source->at(rand() % source->size()));

		player_info_t pInfo;
		if (gInts.Engine->GetPlayerInfo(vid, &pInfo))
		{
			Util->ReplaceString(msg, "%name%", pInfo.name);
			Util->ReplaceString(msg, "% name %", pInfo.name);
		}
		/*	Util->ReplaceString(msg, "\n", "\x0D");*/
		gInts.Engine->ClientCmd(msg.c_str());



	}
}