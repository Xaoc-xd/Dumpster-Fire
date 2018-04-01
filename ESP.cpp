#include "ESP.h"
#include "CDrawManager.h"
/*

aaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAAAAAAAAAAHHHHHHHHHHHHHHHHHHHH
read if gay :)

*/
CESP gESP;

void CESP::Run(CBaseEntity* pLocal)
{
	if (gCvars.misc_cleanScreenshot)
	{
		if (gInts.Engine->IsTakingScreenshot() || GetAsyncKeyState(VK_F12) || GetAsyncKeyState(VK_SNAPSHOT))
		{
			return;
		}
	}
	if (!gCvars.esp_active)
		return;

	for (int i = 1; i <= gInts.Engine->GetMaxClients(); i++)
	{
		if (i == me)
			continue;

		CBaseEntity* pEntity = GetBaseEntity(i);

		if (!pEntity)
			continue;

		if (pEntity->IsDormant())
			continue;

		if (pEntity->GetLifeState() != LIFE_ALIVE)
			continue;

		if (gCvars.esp_enemyonly && pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;

		Player_ESP(pLocal, pEntity);
	}
}

void CESP::Player_ESP(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
	player_info_t pInfo;
	if (!gInts.Engine->GetPlayerInfo(pEntity->GetIndex(), &pInfo))
		return;

	const matrix3x4& vMatrix = pEntity->GetRgflCoordinateFrame();

	Vector vMin = pEntity->GetCollideableMins();
	Vector vMax = pEntity->GetCollideableMaxs();

	Vector vPointList[] = {
		Vector(vMin.x, vMin.y, vMin.z),
		Vector(vMin.x, vMax.y, vMin.z),
		Vector(vMax.x, vMax.y, vMin.z),
		Vector(vMax.x, vMin.y, vMin.z),
		Vector(vMax.x, vMax.y, vMax.z),
		Vector(vMin.x, vMax.y, vMax.z),
		Vector(vMin.x, vMin.y, vMax.z),
		Vector(vMax.x, vMin.y, vMax.z)
	};

	Vector vTransformed[8];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
			vTransformed[i][j] = vPointList[i].Dot((Vector&)vMatrix[j]) + vMatrix[j][3];

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	if (!gDraw.WorldToScreen(vTransformed[3], flb) ||
		!gDraw.WorldToScreen(vTransformed[0], blb) ||
		!gDraw.WorldToScreen(vTransformed[2], frb) ||
		!gDraw.WorldToScreen(vTransformed[6], blt) ||
		!gDraw.WorldToScreen(vTransformed[5], brt) ||
		!gDraw.WorldToScreen(vTransformed[4], frt) ||
		!gDraw.WorldToScreen(vTransformed[1], brb) ||
		!gDraw.WorldToScreen(vTransformed[7], flt))
		return; 

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	float x = left;
	float y = bottom;
	float w = right - left;
	float h = top - bottom;

	x += ((right - left) / 8); //pseudo fix for those THICC boxes
	w -= ((right - left) / 8) * 2;

	Color clrPlayerCol = gDraw.GetPlayerColor(pEntity);
	Color clrBoneCol = gCvars.esp_bones == 1 ? Color::White() : gCvars.esp_bones == 2 ? Color::Green() : clrPlayerCol;
	int iY = 0;
	//iHp is only for health bar
	int iHp = pEntity->GetHealth(), iMaxHp = pEntity->GetMaxHealth();
	if (iHp > iMaxHp)
		iHp = iMaxHp;

	if (gCvars.esp_box) {
		for (int i = 0; i < gCvars.esp_box_thickness; i++)
		{
			gDraw.OutlineRect(x + i, y + i, w - i * 2, h - i * 2, clrPlayerCol);
		}
	}

	if (gCvars.esp_removeDisguise)
	{
		int curCond = pEntity->GetCond();
		if (curCond & tf_cond::TFCond_Disguised)
			pEntity->SetCond(curCond & ~tf_cond::TFCond_Disguised);
	}
	if (gCvars.esp_removeCloak)
	{
		int curCond = pEntity->GetCond();
		if (curCond & tf_cond::TFCond_Cloaked)
			pEntity->SetCond(curCond & ~tf_cond::TFCond_Cloaked);
	}
	if (gCvars.esp_removeTaunt)
	{
		int curCond = pEntity->GetCond();
		if (curCond & tf_cond::TFCond_Taunting)
			pEntity->SetCond(curCond & ~tf_cond::TFCond_Taunting);
	}

	if (gCvars.esp_health == 2 || gCvars.esp_health == 3)
	{
		gDraw.OutlineRect(x - 6, y - 1, 5, h, Color::Black());
		gDraw.DrawRect(x - 5, y + (h - (h / iMaxHp * iHp)) - 1, 3, h / iMaxHp * iHp, Color::Green());
	}

	if (gCvars.esp_name)
	{
		gDraw.DrawString(x + w + 2, y + iY, clrPlayerCol, pInfo.name);
		iY += gDraw.GetESPHeight();
	}

	if (gCvars.esp_class)
	{
		gDraw.DrawString(x + w + 2, y + iY, clrPlayerCol, "%s", pEntity->szGetClass());
		iY += gDraw.GetESPHeight();
	}

	if (gCvars.esp_health == 1 || gCvars.esp_health == 3)
	{
		gDraw.DrawString(x + w + 2, y + iY, Color::Green(), "%d HP", pEntity->GetHealth());
		iY += gDraw.GetESPHeight();
	}

	if (gCvars.esp_bones) //bones
	{
		static int iLeftArmBones[] = { 8, 7, 6, 4 };
		static int iRightArmBones[] = { 11, 10, 9, 4 };
		static int iHeadBones[] = { 0, 4, 1 };
		static int iLeftLegBones[] = { 14, 13, 1 };
		static int iRightLegBones[] = { 17, 16, 1 };

		DrawBone(pEntity, iLeftArmBones, 4, clrBoneCol);
		DrawBone(pEntity, iRightArmBones, 4, clrBoneCol);

		DrawBone(pEntity, iHeadBones, 3, clrBoneCol);

		DrawBone(pEntity, iLeftLegBones, 3, clrBoneCol);
		DrawBone(pEntity, iRightLegBones, 3, clrBoneCol);
	}

	if (gCvars.esp_face)
		DrawFace(pEntity, clrPlayerCol);
	int pBaseEntityCond = pEntity->GetCond();
	{
		if (pBaseEntityCond& TFCond_Cloaked)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Cloaked]");
			iY += gDraw.GetESPHeight();
		}
		if (pBaseEntityCond& TFCond_Disguised)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Disguised]");
			iY += gDraw.GetESPHeight();
		}
		if (pBaseEntityCond& TFCond_Bonked)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Bonked]");
			iY += gDraw.GetESPHeight();
		}
		if (pBaseEntityCond& TFCond_Slowed)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Slowed]");
			iY += gDraw.GetESPHeight();
		}
		if (pBaseEntityCond& TFCond_OnFire)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Burning]");
			iY += gDraw.GetESPHeight();
		}
		if (pBaseEntityCond& TFCond_Zoomed)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Zoomed]");
			iY += gDraw.GetESPHeight();
		}
		if (pBaseEntityCond& TFCond_Jarated)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Jarated]");
			iY += gDraw.GetESPHeight();
		}
		if ((pBaseEntityCond& TFCond_Ubercharged) || (pBaseEntityCond& TFCond_MegaHeal))
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Ubered]");
			iY += gDraw.GetESPHeight();
		}
		else if (pBaseEntityCond& TFCond_UberchargeFading)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Uber Fading]");
			iY += gDraw.GetESPHeight();
		}
		if (pBaseEntityCond& TFCond_Healing)
		{
			gDraw.DrawString(x + w + 2, y + iY, Color::White(), "[Over Healed]");
			iY += gDraw.GetESPHeight();
		}
		if (pBaseEntityCond& TFCond_Disguised && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_Disguised;
		}
		if (pBaseEntityCond& TFCond_Cloaked && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_Cloaked;
		}
		if (pBaseEntityCond& TFCond_Slowed && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_Slowed;
		}
		if (pBaseEntityCond& TFCond_OnFire && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_OnFire;
		}
		if (pBaseEntityCond& TFCond_Bonked && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_Bonked;
		}
		if (pBaseEntityCond& TFCond_Zoomed && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_Zoomed;
		}
		if (pBaseEntityCond& TFCond_Jarated && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_Jarated;
		}
		if (pBaseEntityCond& TFCond_Ubercharged && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_Ubercharged;
		}
		if (pBaseEntityCond& TFCond_UberchargeFading && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_UberchargeFading;
		}
		if (pBaseEntityCond& TFCond_Healing && gCvars.esp_playerCond)
		{
			pBaseEntityCond &= ~TFCond_Healing;
		}
	}
}

void CESP::DrawFace(CBaseEntity* pEntity, Color clr)
{
	Vector head = pEntity->GetHitboxPosition(0);
	Vector screen;

	if (!gDraw.WorldToScreen(head, screen))
		return;

	gDraw.DrawRect(screen.x, screen.y, 25, 25, clr);
	gDraw.DrawRect(screen.x + 5, screen.y + 5, 2, 2, Color::Black()); // left eye
	gDraw.DrawRect(screen.x + 5, screen.y + 10, 2, 2, Color::Black());
	gDraw.DrawRect(screen.x + 15, screen.y + 3, 3, 15, Color::Black());

}
	 //My code, but creds to f1ssion for giving me the idea
void CESP::DrawBone(CBaseEntity* pEntity, int* iBones, int count, Color clrCol)
{
	for (int i = 0; i < count; i++)
	{
		if (i == count - 1)
			continue;

		Vector vBone1 = pEntity->GetHitboxPosition(iBones[i]);
		Vector vBone2 = pEntity->GetHitboxPosition(iBones[i + 1]);

		Vector vScr1, vScr2;

		if (!gDraw.WorldToScreen(vBone1, vScr1) || !gDraw.WorldToScreen(vBone2, vScr2))
			continue;

		gDraw.DrawLine(vScr1.x, vScr1.y, vScr2.x, vScr2.y, clrCol);
	}
}