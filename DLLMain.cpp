#include "SDK.h"
#include "Client.h"
#include "Panels.h"
#include "KillSay.h"

COffsets gOffsets;
CGlobalVariables gCvars;
CInterfaces gInts;

CreateInterface_t EngineFactory = NULL;
CreateInterface_t ClientFactory = NULL;
CreateInterface_t VGUIFactory = NULL;
CreateInterface_t VGUI2Factory = NULL;
CreateInterface_t CvarFactory = NULL;
// being gay isnt wrong
// being gay is very, very wrong
// no homo zone
// test 123456
// 10.0.15063.0
//TEST AAAAA
typedef void(__thiscall *OverrideViewFn) (void*, CViewSetup*);

void __fastcall Hooked_OverrideView(void* _this, void* _edx, CViewSetup* pSetup) // credits, ActualCheats and outi - plasma
{

	// epic code
	VMTManager& hook = VMTManager::GetHook(_this); //Get a pointer to the instance of your VMTManager with the function GetHook.
	hook.GetMethod<OverrideViewFn>(16)(_this, pSetup); //Call the original.
	if (!gInts.Engine->IsInGame() && !gInts.Engine->IsConnected())
		return;

	if (pSetup->m_fov != 20.0f && pSetup->m_fov != gCvars.misc_fov) // no delet this, important for when zoomed- plasma
	{
		pSetup->m_fov = gCvars.misc_fov;
	}
}
static int vacUndetected = 1; //the encryption method cheat devs don't want you to know

#include "InputSys.h"
#include "Menu.h"

CreateInterfaceFn SteamFactory = NULL;
DWORD WINAPI dwMainThread( LPVOID lpArguments )
{
	if (gInts.Client != NULL)
		return 0;

	VMTBaseManager* clientHook = new VMTBaseManager();
	VMTBaseManager* clientModeHook = new VMTBaseManager();
	VMTBaseManager* panelHook = new VMTBaseManager();

	ClientFactory = ( CreateInterfaceFn ) GetProcAddress( gSignatures.GetModuleHandleSafe( "client.dll" ), "CreateInterface" );
	EngineFactory = (CreateInterfaceFn)GetProcAddress(gSignatures.GetModuleHandleSafe("engine.dll"), "CreateInterface");
	CvarFactory = (CreateInterfaceFn)GetProcAddress(gSignatures.GetModuleHandleSafe("vstdlib.dll"), "CreateInterface");
	VGUIFactory = (CreateInterfaceFn)GetProcAddress(gSignatures.GetModuleHandleSafe("vguimatsurface.dll"), "CreateInterface");
	SteamFactory = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA("SteamClient.dll"), "CreateInterface");


	gInts.Client = ( CHLClient* )ClientFactory( "VClient017", NULL);
	gInts.EntList = ( CEntList* ) ClientFactory( "VClientEntityList003", NULL );
	gInts.Engine = ( EngineClient* ) EngineFactory( "VEngineClient013", NULL );
	gInts.Surface = ( ISurface* ) VGUIFactory( "VGUI_Surface030", NULL );
	gInts.cvar = (ICvar*)CvarFactory("VEngineCvar004", NULL);
	gInts.EngineTrace = ( IEngineTrace* ) EngineFactory( "EngineTraceClient003", NULL );
	gInts.ModelInfo = ( IVModelInfo* ) EngineFactory( "VModelInfoClient006", NULL );
	gInts.EventManager = (IGameEventManager2*)EngineFactory("GAMEEVENTSMANAGER002", NULL);
	gInts.steamclient = (ISteamClient017*)SteamFactory("SteamClient017", NULL);

	HSteamPipe hNewPipe = gInts.steamclient->CreateSteamPipe();
	HSteamUser hNewUser = gInts.steamclient->ConnectToGlobalUser(hNewPipe);

	gInts.steamfriends = reinterpret_cast<ISteamFriends002 *>(gInts.steamclient->GetISteamFriends(hNewUser, hNewPipe, STEAMFRIENDS_INTERFACE_VERSION_002));
	gInts.steamuser = reinterpret_cast<ISteamUser017 *>(gInts.steamclient->GetISteamUser(hNewUser, hNewPipe, STEAMUSER_INTERFACE_VERSION_017));

	XASSERT(gInts.Client);
	XASSERT(gInts.EntList);
	XASSERT(gInts.Engine);
	XASSERT(gInts.Surface);
	XASSERT(gInts.EngineTrace);
	XASSERT(gInts.ModelInfo);
	XASSERT(gInts.steamclient);
	XASSERT(gInts.steamfriends);
	XASSERT(gInts.steamuser);

	InputSys::Get().Initialize();

	InputSys::Get().RegisterHotkey(VK_INSERT, [lpArguments]()
	{
		Menu::Get().Toggle();
	});

	InputSys::Get().RegisterHotkey(VK_LBUTTON, [lpArguments]()
	{
		Menu::Get().Click();
	});

	Font::Get().Create();
	Menu::Get().Init();


	//Setup the Panel hook so we can draw.
	if( !gInts.Panels )
	{
		VGUI2Factory = (CreateInterfaceFn)GetProcAddress(gSignatures.GetModuleHandleSafe("vgui2.dll"), "CreateInterface");
		gInts.Panels = ( IPanel* ) VGUI2Factory( "VGUI_Panel009", NULL );
		XASSERT( gInts.Panels );

		if( gInts.Panels )
		{
			panelHook->Init(gInts.Panels);
			panelHook->HookMethod(&Hooked_PaintTraverse, gOffsets.iPaintTraverseOffset);
			panelHook->Rehook();
		}
	}

	gInts.globals = *reinterpret_cast<CGlobals **>(gSignatures.GetEngineSignature("A1 ? ? ? ? 8B 11 68") + 8);
	XASSERT(gInts.globals);

	DWORD dwClientModeAddress = gSignatures.GetClientSignature("8B 0D ? ? ? ? 8B 02 D9 05");
	XASSERT(dwClientModeAddress);
	gInts.ClientMode = **(ClientModeShared***)(dwClientModeAddress + 2);
	LOGDEBUG("g_pClientModeShared_ptr client.dll+0x%X", (DWORD)gInts.ClientMode - dwClientBase);
			
	clientHook->Init(gInts.Client);
	clientHook->HookMethod(&Hooked_KeyEvent, gOffsets.iKeyEventOffset);
	clientHook->HookMethod(&Hooked_FrameStageNotify, gOffsets.iFrameStageNotifyOffset);
	clientHook->Rehook();

	clientModeHook->Init(gInts.ClientMode);
	clientModeHook->HookMethod(&Hooked_CreateMove, gOffsets.iCreateMoveOffset); //ClientMode create move is called inside of CHLClient::CreateMove, and thus no need for hooking WriteUserCmdDelta.
	clientModeHook->HookMethod(&Hooked_OverrideView, 16);
	clientModeHook->Rehook();

	gInts.cvar->ConsolePrintf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "______________________________________________________________________________\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Dumpster Fire Successfully Injected!\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Credits\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Hold On\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "channel32\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "AVexxed\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Wolfie\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Apple\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Lemon\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Castle\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "czcv333\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "inhonia\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Tohfu\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "Chris\n");
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "______________________________________________________________________________\n");
	CSteamID localID = gInts.steamuser->GetSteamID();
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "PersonalName: %s\n", gInts.steamfriends->GetPersonaName());
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "SteamID: %s\n", localID.Render());
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "newSteamID:  %s\n", localID.SteamRender());
	gInts.cvar->ConsoleColorPrintf(Color(15, 150, 150, 255), "______________________________________________________________________________\n");


	///TODO: Add the announcer here... soon:tm:
	gKillSay.InitKillSay();

	return 0; //The thread has been completed, and we do not need to call anything once we're done. The call to Hooked_PaintTraverse is now our main thread. Read if gay.
}

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		Log::Init(hInstance);
		CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)dwMainThread, NULL, 0, NULL ); 
	}
	return true;
}
