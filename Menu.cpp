#include "Menu.h"

void Menu::Init()
{
	m_isVisible = false;

	CWindow Main(100, 100, 345, 150);

#pragma region AimTab
	auto AimTab = new CChild(0, 0, 120, L"Aimbot");

	// Original example controls
	AimTab->AddControl(new CCheckBox(L"Enabled", &gCvars.aimbot_active));
	AimTab->AddControl(new CCheckBox(L"Autoshoot", &gCvars.aimbot_autoshoot));
	AimTab->AddControl(new CSlider<int>(L"Hitbox", 0, 17, &gCvars.aimbot_hitbox));

	Main.AddControl(AimTab);
#pragma endregion
#pragma region Misc
	auto Misc = new CChild(130, 0, 190, L"Misc");

	/*Misc->AddControl(new CCheckBox(L"Backtrack", &g_Options.MISC_Backtrack));
	Misc->AddControl(new CCheckBox(L"Auto-Accept", &g_Options.MISC_AutoAccept));
	Misc->AddControl(new CCheckBox(L"Bunnyhop", &g_Options.MISC_Bunnyhop));
	Misc->AddControl(new CCheckBox(L"Reveal Ranks", &g_Options.MISC_RankReveal));
	Misc->AddControl(new CSlider<int>(L"Viewmodel FOV", 0, 40, &g_Options.MISC_ViewmodelFOV));
	Misc->AddControl(new CTextBox(80, 16, L"Clan Tag", &g_Options.MISC_ClanTag));
	Misc->AddControl(new CButton(80, 16, L"Load Skins", []() { Skinchanger::Get().LoadSkins(); }));*/

	Main.AddControl(Misc);
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