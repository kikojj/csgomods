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
#include "SDK/Utils/Item.hpp"

#include "Utils/GlobalVars.hpp"
#include "Utils/Helpers/Helpers.hpp"
#include "Utils/Memory/Memory.hpp"
#include "Utils/Memory/Modules.hpp"
#include "Utils/BspParser/BspParser.hpp"
#include "Utils/Settings/Settings.hpp"
#include "Utils/Offsets/Offsets.hpp"
#include "Utils/VisibleCheck/VisibleCheck.hpp"
#include "Utils/ClientCmd/ClientCmd.hpp"
#include "Utils/ClientCmd/CMDToggle.hpp"

using namespace std;

#pragma region Global Vars
c_menu_server g_menu_server;

c_memory g_mem;
s_pm_module g_client_dll;
s_pm_module g_engine_dll;

c_client g_client;
c_engine g_engine;

rn::bsp_parser g_bsp_parser;
c_visible_check g_visible_check;

map<c_item::en_defenition_index, int> g_model_indexes;
c_client_cmd g_client_cmd;

bool g_b_working = true;
#pragma endregion

c_visuals visuals;
c_aim_bot aim_bot;
c_trigger_bot trigget_bot;
c_skinchanger skinchanger;
c_misc misc;

CMDToggle mouse_bind("bind mouse1 +attack", "unbind mouse1");

int main() {
	try {
		cout << "[Main]: Waiting for process '" << GAME_NAME << "'." << endl;
		while (!g_mem.find_process(GAME_NAME)) {
			Sleep(100);
		}
		cout << "[Main]: Process '" << GAME_NAME << "' was found. Starting..." << endl;
		Sleep(5000);

		g_mem.attach(g_mem.find_process(GAME_NAME), PROCESS_ALL_ACCESS);
		cout << "[Main]: Attached in process '" << GAME_NAME << "'." << endl;

		g_client_dll = g_mem.get_module(CLIENT_DLL_NAME);
		while (!g_client_dll.base || !g_client_dll.size) {
			Sleep(100);
			g_client_dll = g_mem.get_module(CLIENT_DLL_NAME);
		}
		cout << "[Main]: Module '" << CLIENT_DLL_NAME << "' loaded. Base: " << g_client_dll.base << endl;

		g_engine_dll = g_mem.get_module(ENGINE_DLL_NAME);
		while (!g_engine_dll.base || !g_engine_dll.size) {
			Sleep(100);
			g_engine_dll = g_mem.get_module(ENGINE_DLL_NAME);
		}
		cout << "[Main]: Module '" << ENGINE_DLL_NAME << "' loaded. Base: " << g_engine_dll.base << endl;

		c_offsets::init();
		c_settings::get_from_file("default.json");
		g_client_cmd.init();

		g_client_cmd.execute("clear");
		g_client_cmd.execute("echo [CSGOMODS]: Started.");
		g_client_cmd.execute(string(string("echo [CSGOMODS]: You can open menu, using steam overlay(localhost:") + to_string(HTTP_SERVER_PORT) + string(")")).c_str());
		g_client_cmd.execute("echo [CSGOMODS]: Sorry, I will unbind your mouse1 button when needed. I need it to make my aim bot work better.");
		g_client_cmd.execute("echo [CSGOMODS]: You can still shoot whenever you want, but you must safely exit the cheat (press exit in the menu) to restore bind automatically, or exit at your own discretion and restore the bind yourself if necessary! Thank:)");
		(c_settings::aimbot_enable ? mouse_bind.off() : mouse_bind.on());

		#pragma region Threads
		thread th_menu_data([]() {
			int i_last_active_weapon_item_di = -1;
			en_team_num last_team = en_team_num::Invalid;
			while (g_b_working) {
				if (g_engine.client_state->state() != en_client_states::InGame || g_engine.client_state->delta_tick() == -1) {
					continue;
				}

				//Radar Data
				vector<s_radar_data> vec_radar_data;
				for (const auto& entity_object : g_client.entity_list->players()) {
					c_base_player player(entity_object.first);

					auto player_info = player.info();
					auto vec3_position = player.m_vec3_origin();

					vec_radar_data.push_back({
							player_info.name,
							player_info.user_id,
							player.team_num(),
							player_info.is_fake_player,

							player.ping(),
							player.m_i_account(),
							player.kills(),
							player.assists(),
							player.deaths(),
							player.mvps(),
							player.score(),

							player.competitive_ranking(),
							player.competitive_wins(),

							vec3_position.x,
							vec3_position.y,
							vec3_position.z
						});
				}
				g_menu_server.get_radar_data(vec_radar_data);

				if (g_client.local_player->m_i_health() <= 0 || g_client.local_player->team_num() < en_team_num::Terrorist) {
					continue;
				}

				//My active Weapon
				int i_active_weapon_id = g_client.local_player->m_h_active_weapon() & 0xfff;
				c_base_weapon activeWeapon(g_client.entity_list->get_by_id(i_active_weapon_id - 1));
				auto i_active_weapon_item_di = (int)activeWeapon.item_di();

				if (i_active_weapon_item_di != (int)c_item::en_defenition_index::Invalid && i_active_weapon_item_di != i_last_active_weapon_item_di) {
					i_last_active_weapon_item_di = i_active_weapon_item_di;
					g_menu_server.get_active_weapon(i_active_weapon_item_di);
				}

				//My team
				auto team = g_client.local_player->team_num();
				if (last_team != team) {
					last_team = team;
					g_menu_server.get_team(team);
				}

				Sleep(500);
			}
		});

		thread th_menu_server([]() {
			g_menu_server.start();
		});

		thread th_menu_open([]() { while (g_b_working) {
			if (GetAsyncKeyState(VK_INSERT)) {
				c_helpers::toggle_steam_overlay();
				Sleep(1000);
			}
		}});

		thread th_visuals([]() { while (g_b_working) {
			visuals.loop();
			Sleep(1);
		}});

		thread th_skinchanger([]() { while (g_b_working) {
			skinchanger.loop();
			//Sleep(1);
		}});		

		thread th_misc_radar([]() { while (g_b_working) {
			misc.radar_hack();
			Sleep(1);
		}});

		thread th_misc_bhop([]() { while (g_b_working) {
			misc.bhop();
			Sleep(1);
		}});

		thread th_misc_auto_accept([]() { while (g_b_working) {
			misc.auto_accept();
			Sleep(1);
		}});

		thread th_misc_anti_flash([]() { while (g_b_working) {
			misc.anti_flash();
			Sleep(1);
		}});

		thread th_map([]() {
			auto i_last_client_state = 0;
			while (g_b_working) {
				auto state = g_engine.client_state->state();
				if (state == en_client_states::InGame && i_last_client_state != (int)state) {
					while (g_client.local_player->team_num() != en_team_num::Terrorist && g_client.local_player->team_num() != en_team_num::CounterTerrorist) {
						Sleep(100);
					}

					//for bsp parser
					auto gameDir = g_engine.game_dir().data();
					auto mapDir = g_engine.client_state->map_directory().data();

					//bsp now is not in use
					//bsp_parser.load_map(gameDir, mapDir);

					g_menu_server.get_map_name(string(mapDir));

					//for skinchanger
					c_helpers::update_model_indexes();
				}
				i_last_client_state = (int)state;

				Sleep(1);
			}
		});

		thread th_visible_check([]() {
			while (g_b_working) {
				while (!g_visible_check.init()) {}
				if (g_engine.client_state->delta_tick() == -1 || g_engine.client_state->state() != en_client_states::InGame) {
					continue;
				}
				g_visible_check.update_visible_struct();
			}
		});

		thread th_shoot([]() {
			bool b_last_aim_state = c_settings::aimbot_enable;
			while (g_b_working) {
				bool b_should_shoot = GetAsyncKeyState(VK_LBUTTON) && c_helpers::is_mouse_active();

				aim_bot.loop();
				trigget_bot.loop();
				misc.auto_pistols();

				int i_active_weapon_id = g_client.local_player->m_h_active_weapon() & 0xfff;
				c_base_weapon activeWeapon(g_client.entity_list->get_by_id(i_active_weapon_id - 1));

				if (b_should_shoot) {
					if (c_settings::aimbot_enable && aim_bot.should_wait && !aim_bot.should_shoot) {
						g_client.dw_force_attack(en_key_event::KeyUp);
					}
					else {
						if (c_settings::misc_auto_pistols_enable && (misc.should_wait || !misc.should_shoot) && activeWeapon.is_pistol()) {
							g_client.dw_force_attack(en_key_event::KeyUp);
						}
						else {
							g_client.dw_force_attack(en_key_event::KeyDown);
						}
					}
				}
				else {
					if (c_settings::triggerbot_enable && !trigget_bot.should_wait && trigget_bot.should_shoot) {
						g_client.dw_force_attack(en_key_event::KeyDown);
					}
					else {
						g_client.dw_force_attack(en_key_event::KeyUp);
					}
				}

				if (b_last_aim_state != c_settings::aimbot_enable) {
					(c_settings::aimbot_enable ? mouse_bind.off() : mouse_bind.on());
					b_last_aim_state = c_settings::aimbot_enable;
				}

				Sleep(1);
			}
		});

		thread th_working([]() {
			while (g_b_working) {
				while (g_mem.find_process(GAME_NAME)) {
					Sleep(500);
				}
				g_menu_server.stop();
			}
		});

		th_menu_server.join();
		th_menu_data.join();
		th_menu_open.join();
		th_visuals.join();
		th_skinchanger.join();
		th_misc_radar.join();
		th_misc_bhop.join();
		th_misc_anti_flash.join();
		th_map.join();
		th_visible_check.join();
		th_shoot.join();
		th_working.join();
		#pragma endregion

		if (g_mem.find_process(GAME_NAME)) {
			mouse_bind.on();
			g_client_cmd.execute("echo [CSGOMODS]: Mouse1 bind was restored.");
		}
		c_helpers::exit();
	}
	catch (const exception& err){
		cout << "[Main]: Catch. Error: '" << err.what() << endl;
	}
	return 0;
}