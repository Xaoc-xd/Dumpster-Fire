#pragma once
#include "SDK.h"

class CUtil
{
public:
	void VectorTransform(const Vector& vSome, const matrix3x4& vMatrix, Vector& vOut);

	float RandFloatRange(float min, float max);

	bool IsVisible(void* pLocal, void* pEntity, Vector vStart, Vector vEnd);

	bool IsKeyPressed(int i);

	bool IsHeadshotWeapon(CBaseEntity* pLocal, CBaseCombatWeapon* pWep);

	void silentMovementFix(CUserCmd *pUserCmd, Vector angles);
	
	PVOID InitKeyValue();

	template<typename T, typename... Targs>
	void format_internal(std::stringstream& stream, T value, Targs... args)
	{
		stream << value;
		format_internal(stream, args...);
	}
	template<typename... Args>
	std::string format(const Args&... args)
	{
		std::stringstream stream;
		format_internal(stream, args...);
		return stream.str();
	}

};
extern CUtil* Util;