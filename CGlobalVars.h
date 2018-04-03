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
	bool aimbot_active;
	float aimbot_key;
	bool aimbot_hitscan;
	int aimbot_hitbox;
	bool aimbot_autoshoot;
	float aimbot_fov = 180;
	bool aimbot_silent;
	bool aimbot_zoomedonly;
	bool aimbot_ignore_cloak;
	bool aimbot_smooth;
	int aimbot_smooth_amt;

	float triggerbot_switch;
	bool triggerbot_active;
	int triggerbot_key;
	bool triggerbot_headonly;

	float esp_switch;
	bool esp_active;
	bool esp_enemyonly;
	bool esp_box;
	int esp_box_thickness = 1;
	bool esp_name;
	bool esp_class;
	bool esp_removeDisguise;
	bool esp_removeCloak;
	bool esp_removeTaunt;
	bool esp_playerCond_enabled;
	int esp_playerCond;
	bool esp_health_enabled;
	int esp_health;
	bool esp_bones_enabled;
	int esp_bones;
	bool esp_face;
	bool esp_crosshair;

	float aa_switch;
	int aa_pitch;
	float aa_pitch_fakeup;
	float aa_pitch_fakedown;
	int aa_yaw;
	float aa_yaw_staticjitter;
	float aa_yaw_right;
	float aa_yaw_left;
	bool aa_enabled;
	bool aa_pitch_enabled;
	bool aa_yaw_enabled;

	float removecond_switch;
	bool removecond_enabled;
	int removecond_value;
	int removecond_key;
	bool removecond_autoinstantcap;
	bool removecond_instantweaponswitch;
	bool removecond_automedkit;
	bool removecond_stickyspam;

	float misc_switch;
	bool misc_thirdPerson;
	bool misc_bunnyhop;
	bool misc_autostrafe;
	bool misc_autobackstab;
	bool misc_noisemaker_spam;
	bool misc_noscope;
	bool misc_chatspam_enabled;
	int misc_chatspam_selection;
	bool misc_cleanScreenshot;
	int misc_chatspam_delay;
	bool misc_killsay_enabled;
	int misc_killsay_selection;
	bool misc_roll_speedhack;
	bool misc_wowsweet;
	bool misc_voice;
	int misc_fov = 90;// = 90; // why the fuck would u start at 70 - plasma // someone on steamcommunity said default was 70 - wolfie
	int misc_viewmodel_fov = 70;// = 70;
	bool misc_no_push;



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