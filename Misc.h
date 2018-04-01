#pragma once
#include "SDK.h"

class CMisc
{
public:

	void Run(CBaseEntity* pLocal, CUserCmd* pCommand);

private:
	float fLastTime;
	//Other funcs

	void NoisemakerSpam(PVOID kv);
};

extern CMisc gMisc;