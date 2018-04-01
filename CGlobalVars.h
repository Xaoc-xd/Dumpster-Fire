#include "SDK.h"

class CGlobalVariables
{
public:
	int iAimbotIndex = -1;
	
	float settings_switch;
	float iMenu_Pos_X = 16;
	float iMenu_Pos_Y = 32;
	float szsubstest;

	float aimbot_switch;
	float aimbot_active;
	float aimbot_key;
	float aimbot_hitscan;
	float aimbot_hitbox;
	float aimbot_autoshoot;
	float aimbot_fov = 180;
	float aimbot_silent;
	float aimbot_zoomedonly;
	float aimbot_ignore_cloak;
	float aimbot_smooth;
	float aimbot_smooth_amt;

	float triggerbot_switch;
	float triggerbot_active;
	float triggerbot_key;
	float triggerbot_headonly;

	float esp_switch;
	float esp_active;
	float esp_enemyonly;
	float esp_box;
	float esp_box_thickness = 1;
	float esp_name;
	float esp_class;
	float esp_health;
	float esp_bones;
	float esp_face;

	float removecond_switch;
	float removecond_enabled;
	float removecond_value;
	float removecond_key;
	float removecond_autoinstantcap;
	float removecond_instantweaponswitch;
	float removecond_automedkit;
	float removecond_stickyspam;

	float misc_switch;
	float misc_thirdPerson;
	float misc_bunnyhop;
	float misc_autostrafe;
	float misc_autobackstab;
	float misc_noisemaker_spam;
	float misc_noscope;
	float misc_chatspam_selection;
	float misc_chatspam_delay;
	float misc_killsay_selection;
	float misc_roll_speedhack;
	float misc_wowsweet;

	float playerlist_switch;
	float PlayerMode[64] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
};

class COffsets
{
public:
	int iKeyEventOffset = 20, iCreateMoveOffset = 21, iPaintTraverseOffset = 41;
};