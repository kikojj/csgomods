#include <iostream>
#include <thread>
#include <map>

#include "GlobalVars.hpp"
#include "MenuServer.hpp"
#include "Defines.hpp"
#include "Memory.hpp"
#include "Modules.hpp"
#include "Client.hpp"
#include "Engine.hpp"

#include "bsb-parser/bsp_parser.hpp"

#include "Settings.hpp"
#include "Offsets.hpp"

#include "Visuals.hpp"
#include "AimBot.hpp"
#include "TriggerBot.hpp"
#include "Skinchanger.hpp"
#include "Misc.hpp"
#include "Helpers.hpp"
#include "visibleCheck/VisibleCheck.h"

using namespace std;

#pragma region Global Vars
MenuServer menuServer;
Memory mem;
PModule clientDll;
PModule engineDll;

Client client;
Engine engine;

rn::bsp_parser bsp_parser;
CVisibleCheck visibleCheck;

map<ItemDefinitionIndex, int> modelIndexes;
#pragma endregion

bool isWorking = true;

Visuals visuals;
AimBot aimBot;
TriggerBot triggetBot;
Skinchanger skinchanger;
Misc misc;

int main() {
	try
	{
		cout << "[Main]: Waiting for process '" << GAME_NAME << "'." << endl;
		while (!mem.Attach(GAME_NAME, PROCESS_ALL_ACCESS)) {
			Sleep(100);
		}
		cout << "[Main]: Attached in process '" << GAME_NAME << "'." << endl;

		clientDll = mem.GetModule(CLIENT_DLL_NAME);
		while (!clientDll.dwBase || !clientDll.dwSize) {
			Sleep(100);
			clientDll = mem.GetModule(CLIENT_DLL_NAME);
		}
		cout << "[Main]: Module '" << CLIENT_DLL_NAME << "' loaded. DwBase: " << clientDll.dwBase << endl;

		engineDll = mem.GetModule(ENGINE_DLL_NAME);
		while (!engineDll.dwBase || !engineDll.dwSize) {
			Sleep(100);
			engineDll = mem.GetModule(ENGINE_DLL_NAME);
		}
		cout << "[Main]: Module '" << ENGINE_DLL_NAME << "' loaded. DwBase: " << engineDll.dwBase << endl;

		Offsets::init();

		Settings::getFromFile("default.json");

		thread thMenuData([]() {
			int lastActiveWeaponIDI = -1;
			TeamNum lastTeam = NO_TEAM;
			while (isWorking) {
				if (
					engine.clientState->state() != INGAME ||
					engine.clientState->m_nDeltaTick() == -1 ||
					client.localPlayer->m_iHealth() <= 0 ||
					client.localPlayer->m_iTeamNum() < TERRORIST
					) {
					continue;
				}

				int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
				BaseCombatWeapon activeWeapon = BaseCombatWeapon(client.entityList->getByID(activeWeaponID - 1));
				auto activeWeaponIDI = (int)activeWeapon.m_iItemDefinitionIndex();

				if (activeWeaponIDI != INVALID_ITEM_DI && activeWeaponIDI != lastActiveWeaponIDI) {
					lastActiveWeaponIDI = activeWeaponIDI;
					menuServer.getActiveWeapon(activeWeaponIDI);
				}

				auto team = client.localPlayer->m_iTeamNum();
				if (lastTeam != team) {
					lastTeam = team;
					menuServer.getTeam(team);
				}
			}

			Sleep(1);
		});

		thread thMenuServer([]() {
			menuServer.start();
		});

		thread thMenuOpen([]() { while (isWorking) {
			if (GetAsyncKeyState(VK_INSERT)) {
				Helpers::toggleSteamOverlay();
				Sleep(1000);
			}
		}});

		thread thVisuals([]() { while (isWorking) {
			visuals.loop();
			Sleep(1);
		}});

		thread thAimBot([]() { while (isWorking) {
			aimBot.loop();
			Sleep(1);
		}});

		thread thTriggerBot([]() { while (isWorking) {
			triggetBot.loop();
			Sleep(1);
		}});

		thread thSkinchanger([]() { while (isWorking) {
			skinchanger.loop();
			//Sleep(1);
		}});		

		thread thMiscRadarHack([]() { while (isWorking) {
			misc.radarHack();
			Sleep(1);
		}});

		thread thMiscBhop([]() { while (isWorking) {
			misc.bhop();
			Sleep(1);
		}});

		thread thMiscAutoPistols([]() { while (isWorking) {
			misc.autoPistols();
			Sleep(1);
		}});

		thread thMiscAutoAccept([]() { while (isWorking) {
			misc.autoAccept();
			Sleep(1);
		}});

		thread thMiscAntiFlash([]() { while (isWorking) {
			misc.antiFlash();
			Sleep(1);
		}});

		thread thMap([]() {
			auto lastClientState = 0;
			while (isWorking) {
				if (engine.clientState->m_nDeltaTick() == -1) {
					continue;
				}
				auto state = engine.clientState->state();
				if (state == INGAME && lastClientState != state) {
					while (client.localPlayer->m_iTeamNum() != TERRORIST && client.localPlayer->m_iTeamNum() != COUNTER_TERRORIST) {
						Sleep(100);
					}

					//for bsp parser
					auto gameDir = engine.dwGameDir().data();
					auto mapDir = engine.clientState->mapDirectory().data();

					bsp_parser.load_map(gameDir, mapDir);

					//for skinchanger
					Helpers::updateModelIndexes();
				}
				lastClientState = state;
			}
		});

		thread thVisibleCheck([]() {
			while (!visibleCheck.init()) {}
			while (true) {
				if (engine.clientState->m_nDeltaTick() == -1) {
					continue;
				}
				visibleCheck.updateVisibleStruct();
			}
		});

		thMenuServer.detach();
		thMenuData.join();
		thMenuOpen.join();
		thVisuals.join();
		thAimBot.join();
		thTriggerBot.join();
		thSkinchanger.join();
		thMiscRadarHack.join();
		thMiscBhop.join();
		thMiscAutoPistols.join();
		thMiscAntiFlash.join();
		thMap.join();
		thVisibleCheck.join();
	}
	catch (const exception& err){
		cout << "[Main]: Catch. Error: '" << err.what() << endl;
	}
	return 0;
}