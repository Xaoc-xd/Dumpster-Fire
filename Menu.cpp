#include "Menu.h"

/*
char* szHealthModes[] = {
	"OFF", "Text", "Bar", "Both",
};

char* szBoneModes[] = {
	"OFF", "White", "Health", "Team",
};

char* szHitboxes[] =
{
	"Auto", "Head", "Pelvis", "Lower Torse", "Lower Mid. Torse", "Upper Mid. Torse", "Upper Torse",
	"Left Upper Arm", "Left Lower Arm", "Left Hand", "Right Upper Arm",
	"Right Lower Arm", "Right Hand", "Left Hip", "Left Knee", "Left Foot",
	"Right Hip", "Right Knee", "Right Foot",
};

char* ChatSpams[] = { "OFF", "NullCore", "LMAOBOX", "Lithium", "Cathook", "Empty Lines", "Speedhook", "Freebox", "Catbot", "Dumpster Fire" };

char* KillSays[] = { "OFF", "NiggerHOOK", "NullCore", "File" };

char* condESP[] = { "OFF", "Dumpster Fire", "NullCore" };*/ // Unneeded, but keep them here for reference.

void Menu::Init()
{
	m_isVisible = false;

	CWindow Main(100, 100, 703, 600);

	// checkbox: 12 pixels

#pragma region Aimbot
	auto AimbotTab = new CChild(0, 0, 220, L"Aimbot");

	AimbotTab->AddControl(new CCheckBox(L"Enabled", &gCvars.aimbot_active));
	AimbotTab->AddControl(new CCheckBox(L"Silent", &gCvars.aimbot_silent));
	AimbotTab->AddControl(new CSlider<int>(L"Field of View", 0, 180, &gCvars.aimbot_fov));
	AimbotTab->AddControl(new CCheckBox(L"Autoshoot", &gCvars.aimbot_autoshoot));
	AimbotTab->AddControl(new CCheckBox(L"Hitscan", &gCvars.aimbot_hitscan));
	AimbotTab->AddControl(new CCombo(&gCvars.aimbot_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" }));
	AimbotTab->AddControl(new CSlider<int>(L"Smooth", 0, 180, &gCvars.aimbot_smooth));
	AimbotTab->AddControl(new CCheckBox(L"Ignore Cloak", &gCvars.aimbot_ignore_cloak));
	AimbotTab->AddControl(new CCheckBox(L"Zoomed Only", &gCvars.aimbot_zoomedonly));
	AimbotTab->AddControl(new CCheckBox(L"Amby", &gCvars.aimbot_waitforcharge));

	Main.AddControl(AimbotTab);
#pragma endregion
#pragma region Triggerbot
	auto TriggerbotTab = new CChild(230, 0, 220, L"Triggerbot");

	TriggerbotTab->AddControl(new CCheckBox(L"Enabled", &gCvars.triggerbot_active));
	TriggerbotTab->AddControl(new CCombo(&gCvars.triggerbot_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" })); // NEEDS LIST
	TriggerbotTab->AddControl(new CCheckBox(L"Head Only", &gCvars.triggerbot_headonly));
	TriggerbotTab->AddControl(new CCheckBox(L"Auto Airblast", &gCvars.triggerbot_autoairblast));
	TriggerbotTab->AddControl(new CCombo(&gCvars.triggerbot_autoairblast_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" })); // NEEDS LIST
	TriggerbotTab->AddControl(new CCheckBox(L"Legit", &gCvars.triggerbot_autoairblast_legit));
	TriggerbotTab->AddControl(new CCheckBox(L"Silent", &gCvars.triggerbot_autoairblast_silent));


	Main.AddControl(TriggerbotTab);
#pragma endregion
#pragma region ESP
	auto ESPTab = new CChild(0, 190, 220, L"ESP");

	ESPTab->AddControl(new CCheckBox(L"Enabled", &gCvars.esp_active));
	ESPTab->AddControl(new CCheckBox(L"Enemies Only", &gCvars.esp_enemyonly));
	ESPTab->AddControl(new CCheckBox(L"Local", &gCvars.esp_local));
	ESPTab->AddControl(new CCheckBox(L"Box", &gCvars.esp_box));
	ESPTab->AddControl(new CCombo(&gCvars.esp_box_selection, { L"Outlined", L"Box", L"Filled", L"Corner" })); 
	ESPTab->AddControl(new CCheckBox(L"Name", &gCvars.esp_name));
	ESPTab->AddControl(new CCheckBox(L"Class", &gCvars.esp_class));
	ESPTab->AddControl(new CCheckBox(L"Weapon", &gCvars.esp_weapons));
	ESPTab->AddControl(new CCheckBox(L"Cond", &gCvars.esp_playerCond_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_playerCond, { L"Dumpster Fire", L"NullCore" })); // NEEDS LIST
	ESPTab->AddControl(new CCheckBox(L"Remove Cloak", &gCvars.esp_removeCloak));
	ESPTab->AddControl(new CCheckBox(L"Remove Disguise", &gCvars.esp_removeDisguise));
	ESPTab->AddControl(new CCheckBox(L"Remove Taunt", &gCvars.esp_removeTaunt));
	ESPTab->AddControl(new CCheckBox(L"Health", &gCvars.esp_health_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_health, { L"Text", L"Bar", L"Both" })); // NEEDS LIST
	ESPTab->AddControl(new CCheckBox(L"Bones", &gCvars.esp_bones_enabled));
	ESPTab->AddControl(new CCombo(&gCvars.esp_bones, { L"White", L"Health", L"Team" })); // NEEDS LIST
	ESPTab->AddControl(new CCheckBox(L"Happy Face", &gCvars.esp_face));
	ESPTab->AddControl(new CCombo(&gCvars.sky_changer_value, { L"None", L"Night", L"Nightfall", L"Harvest Night", L"Halloween" }));
	ESPTab->AddControl(new CCheckBox(L"Crosshair", &gCvars.esp_crosshair));
	ESPTab->AddControl(new CCheckBox(L"Sentry", &gCvars.esp_buildings));
	ESPTab->AddControl(new CCheckBox(L"Box", &gCvars.esp_box_buildings));
	ESPTab->AddControl(new CCombo(&gCvars.esp_health_buildings, { L"Text", L"Bar", L"Both" }));

	Main.AddControl(ESPTab);
#pragma endregion
#pragma region Anti Aim
	auto AntiAimTab = new CChild(230, 142, 220, L"Anti Aim");

	AntiAimTab->AddControl(new CCheckBox(L"Enabled", &gCvars.aa_enabled));
	AntiAimTab->AddControl(new CCheckBox(L"Pitch", &gCvars.aa_pitch_enabled));
	AntiAimTab->AddControl(new CCombo(&gCvars.aa_pitch, { L"Fake Up", L"Up", L"Fake Down", L"Down" })); // NEEDS LIST
	AntiAimTab->AddControl(new CCheckBox(L"Yaw", &gCvars.aa_yaw_enabled));
	AntiAimTab->AddControl(new CCombo(&gCvars.aa_yaw, { L"Right", L"Left", L"Back", L"Random", L"Spin", L"Edge", L"Fake Sideways" })); // NEEDS LIST // Finally, a string that actually uses a unicode character! // Well not anymore...
	AntiAimTab->AddControl(new CSlider<int>(L"Spin Speed", 0, 360, &gCvars.aa_spinspeed));
	AntiAimTab->AddControl(new CCheckBox(L"Resolver", &gCvars.aa_resolver));

	Main.AddControl(AntiAimTab);
#pragma endregion
/*#pragma region Remove Cond
	auto RemoveCondTab = new CChild(230, 262, 220, L"Remove Cond");

	RemoveCondTab->AddControl(new CCheckBox(L"Enabled", &gCvars.removecond_enabled));
	RemoveCondTab->AddControl(new CCombo(&gCvars.removecond_key, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" })); // NEEDS LIST
	RemoveCondTab->AddControl(new CSlider<int>(L"Value", 0, 2500, &gCvars.removecond_value));
	RemoveCondTab->AddControl(new CCheckBox(L"Auto Medkit", &gCvars.removecond_automedkit));
	RemoveCondTab->AddControl(new CCheckBox(L"Auto Instant Cap", &gCvars.removecond_autoinstantcap));
	RemoveCondTab->AddControl(new CCheckBox(L"Instant Weapon Switch", &gCvars.removecond_instantweaponswitch));
	RemoveCondTab->AddControl(new CCheckBox(L"Sticky Spam", &gCvars.removecond_stickyspam));

	Main.AddControl(RemoveCondTab);
#pragma endregion*/
#pragma region Misc
	auto MiscTab = new CChild(460, 0, 220, L"Misc");

	MiscTab->AddControl(new CCheckBox(L"Bunny Hop", &gCvars.misc_bunnyhop));
	MiscTab->AddControl(new CCheckBox(L"Auto Strafe", &gCvars.misc_autostrafe));
	MiscTab->AddControl(new CCheckBox(L"Third Person", &gCvars.misc_thirdPerson));
	MiscTab->AddControl(new CCheckBox(L"Auto Backstab", &gCvars.misc_autobackstab));
	MiscTab->AddControl(new CCheckBox(L"Noisemaker Spam", &gCvars.misc_noisemaker_spam));
	MiscTab->AddControl(new CCheckBox(L"No Scope", &gCvars.misc_noscope));
	MiscTab->AddControl(new CCheckBox(L"No Zoom", &gCvars.misc_nozoom));
	MiscTab->AddControl(new CCheckBox(L"No Push", &gCvars.misc_no_push));
	MiscTab->AddControl(new CCheckBox(L"Chat Spam", &gCvars.misc_chatspam_enabled));
	MiscTab->AddControl(new CCombo(&gCvars.misc_chatspam_selection, { L"NullCore", L"LMAOBOX", L"Lithium", L"Cathook", L"Empty Lines", L"Speedhook", L"Freebox", L"Catbot", L"Dumpster Fire" })); // NEEDS LIST
	MiscTab->AddControl(new CSlider<int>(L"Delay", 1000, 3000, &gCvars.misc_chatspam_delay));
	MiscTab->AddControl(new CSlider<int>(L"Newlines", 0, 32, &gCvars.misc_chatspam_newline));
	MiscTab->AddControl(new CCheckBox(L"Kill Say", &gCvars.misc_killsay_enabled));
	MiscTab->AddControl(new CCombo(&gCvars.misc_killsay_selection, { L"NiggerHOOK", L"NullCore", L"File" })); // NEEDS LIST
	MiscTab->AddControl(new CCheckBox(L"Voice Menu Spam", &gCvars.misc_voice)); // NEEDS LIST (?) // Apple, when you add the options to this feature please add to menu. Thanks. - Wolfie
	MiscTab->AddControl(new CCheckBox(L"Roll Speedhack", &gCvars.misc_roll_speedhack));
	MiscTab->AddControl(new CCheckBox(L"wow sweet", &gCvars.misc_wowsweet));
	MiscTab->AddControl(new CCheckBox(L"Big Heads", &gCvars.misc_bighead));
	MiscTab->AddControl(new CSlider<int>(L"HeadSize", 0, 20, &gCvars.misc_bigheadsize));
	MiscTab->AddControl(new CSlider<int>(L"TorsoSize", 0, 20, &gCvars.misc_torsosize));
	MiscTab->AddControl(new CSlider<int>(L"HandSize", 0, 20, &gCvars.misc_handsize));
	MiscTab->AddControl(new CCheckBox(L"Backtrack", &gCvars.backtrack));
	MiscTab->AddControl(new CCheckBox(L"Server Lagger", &gCvars.misc_lagger));
	MiscTab->AddControl(new CSlider<int>(L"Lagger Power", 1, 100, &gCvars.misc_laggeramt));
//	MiscTab->AddControl(new CCombo(&gCvars.misc_lagkey, { L"Always", L"Mouse 1", L"Mouse 2", L"Mouse 3", L"Mouse 4", L"Mouse 5", L"Shift", L"Alt", L"F" }));
	MiscTab->AddControl(new CCheckBox(L"Clean Screenshot", &gCvars.misc_cleanScreenshot));
	MiscTab->AddControl(new CSlider<int>(L"Field of View", 0, 120, &gCvars.misc_fov));
	MiscTab->AddControl(new CSlider<int>(L"Viewmodel FOV", 0, 120, &gCvars.misc_viewmodel_fov));

	Main.AddControl(MiscTab);
#pragma endregion

	MenuForm.AddWindow(Main);
}

void Menu::Kill()
{}

void Menu::PaintTraverse()
{
	if (m_isVisible)
		MenuForm.Paint();
}

void Menu::Click()
{
	if (m_isVisible)
		MenuForm.Click();
}

void Menu::HandleInput(WPARAM vk)
{
	if (m_isVisible)
		MenuForm.HandleInput(vk);
}

void Menu::Toggle()
{
	m_isVisible = !m_isVisible;
}