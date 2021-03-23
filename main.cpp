#include <iostream>
#include <thread>
#include <map>

#include "MenuServer.hpp"
#include "Visuals.hpp"
#include "AimBot.hpp"
#include "TriggerBot.hpp"
#include "Skinchanger.hpp"
#include "Misc.hpp"

#include "SDK/Utils/Defines.hpp"
#include "SDK/Client/Client.hpp"
#include "SDK/Engine/Engine.hpp"
#include "SDK/Utils/TeamNum.hpp"
#include "SDK/Utils/ItemDefinitionIndex.hpp"

#include "Utils/GlobalVars.hpp"
#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Memory/Memory.hpp"
#include "Utils/Memory/Modules.hpp"
#include "Utils/BspParser/BspParser.hpp"
#include "Utils/Settings/Settings.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/VisibleCheck/VisibleCheck.h"
#include "Utils/ClientCmdUD/ClientCmdUD.hpp"

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
ClientCmdUD clientCmdUD;
#pragma endregion

bool isWorking = true;

Visuals visuals;
AimBot aimBot;
TriggerBot triggetBot;
Skinchanger skinchanger;
Misc misc;

int main() {
	try {
		cout << "[Main]: Waiting for process '" << GAME_NAME << "'." << endl;
		while (!mem.attach(GAME_NAME, PROCESS_ALL_ACCESS)) {
			Sleep(100);
		}
		cout << "[Main]: Attached in process '" << GAME_NAME << "'." << endl;

		clientDll = mem.getModule(CLIENT_DLL_NAME);
		while (!clientDll.dwBase || !clientDll.dwSize) {
			Sleep(100);
			clientDll = mem.getModule(CLIENT_DLL_NAME);
		}
		cout << "[Main]: Module '" << CLIENT_DLL_NAME << "' loaded. DwBase: " << clientDll.dwBase << endl;

		engineDll = mem.getModule(ENGINE_DLL_NAME);
		while (!engineDll.dwBase || !engineDll.dwSize) {
			Sleep(100);
			engineDll = mem.getModule(ENGINE_DLL_NAME);
		}
		cout << "[Main]: Module '" << ENGINE_DLL_NAME << "' loaded. DwBase: " << engineDll.dwBase << endl;

		Offsets::init();
		Settings::getFromFile("default.json");
		clientCmdUD.init();

		clientCmdUD.execute("clear");
		clientCmdUD.execute("echo [CSGOMODS]: Started.");
		clientCmdUD.execute(string(string("echo [CSGOMODS]: You can open menu, using steam overlay(localhost:") + to_string(HTTP_SERVER_PORT) + string(")")).c_str());
		clientCmdUD.execute("unbind mouse1");
		clientCmdUD.execute("echo [CSGOMODS]: Sorry, I have unbinded your mouse1 button. I need it to do my aimbot works better.");
		clientCmdUD.execute("echo [CSGOMODS]: You still can fire, whenever you want, but you should do safe exit from cheat(press exit in menu) to restore your bind automatically or exit as you want and restore bind yourself! Thanks:)");

		#pragma region Threads
		thread thMenuData([]() {
			int lastActiveWeaponIDI = -1;
			TeamNum lastTeam = TeamNum::Invalid;
			while (isWorking) {
				if (
					engine.clientState->state() != ClientStates::INGAME ||
					engine.clientState->m_nDeltaTick() == -1 ||
					client.localPlayer->m_iHealth() <= 0 ||
					client.localPlayer->teamNum() < TeamNum::TERRORIST
					) {
					continue;
				}

				int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
				BaseCombatWeapon activeWeapon(client.entityList->getByID(activeWeaponID - 1));
				auto activeWeaponIDI = (int)activeWeapon.m_iItemDefinitionIndex();

				if (activeWeaponIDI != (int)ItemDefinitionIndex::Invalid && activeWeaponIDI != lastActiveWeaponIDI) {
					lastActiveWeaponIDI = activeWeaponIDI;
					menuServer.getActiveWeapon(activeWeaponIDI);
				}

				auto team = client.localPlayer->teamNum();
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
			//aimBot.loop();
			//Sleep(1);
		}});

		thread thTriggerBot([]() { while (isWorking) {
			//triggetBot.loop();
			//Sleep(1);
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
			//misc.autoPistols();
			//Sleep(1);
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
				if (state == ClientStates::INGAME && lastClientState != (int)state) {
					while (client.localPlayer->teamNum() != TeamNum::TERRORIST && client.localPlayer->teamNum() != TeamNum::COUNTER_TERRORIST) {
						Sleep(100);
					}

					//for bsp parser
					auto gameDir = engine.dwGameDir().data();
					auto mapDir = engine.clientState->mapDirectory().data();

					bsp_parser.load_map(gameDir, mapDir);

					//for skinchanger
					Helpers::updateModelIndexes();
				}
				lastClientState = (int)state;
			}
		});

		thread thVisibleCheck([]() {
			while (isWorking) {
				while (!visibleCheck.init()) {}
				if (engine.clientState->m_nDeltaTick() == -1) {
					continue;
				}
				visibleCheck.updateVisibleStruct();
			}
		});

		thread thShoot([]() {
			while (isWorking) {
				bool shouldShoot = GetAsyncKeyState(VK_LBUTTON) && Helpers::isMouseActive();

				aimBot.loop();
				triggetBot.loop();
				misc.autoPistols();

				if (shouldShoot) {
					if (aimBot.shouldWait && aimBot.shouldShoot || aimBot.shouldWait && !aimBot.shouldShoot) {
						client.dwForceAttack(KeyEvent::KEY_UP);
					}
					else if (
						!aimBot.shouldWait && aimBot.shouldShoot ||
						!aimBot.shouldWait && !aimBot.shouldShoot ||
						!misc.shouldWait && misc.shouldShoot
						) {
						client.dwForceAttack(KeyEvent::KEY_DOWN);
					}
				}
				else {
					if (!triggetBot.shouldWait && triggetBot.shouldShoot) {
						client.dwForceAttack(KeyEvent::KEY_DOWN);
					}
					else {
						client.dwForceAttack(KeyEvent::KEY_UP);
					}
				}

				Sleep(1);
			}
		});

		thMenuServer.join();
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
		#pragma endregion

		clientCmdUD.execute("bind mouse1 +attack");
		clientCmdUD.execute("echo [CSGOMODS]: Mouse1 bind was restored.");
		Helpers::exit();
	}
	catch (const exception& err){
		cout << "[Main]: Catch. Error: '" << err.what() << endl;
	}
	return 0;
}