#pragma once

#include <iostream>
#include <thread>
#include <set>
#include <filesystem>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "SDK/Client/Client.hpp"
#include "SDK/Client/BaseWeapon.hpp"
#include "SDK/Engine/Engine.hpp"
#include "SDK/Utils/TeamNum.hpp"

#include "Utils/GlobalVars.hpp"
#include "Utils/JsonXX/jsonxx.h"
#include "Utils/Settings/Settings.hpp"
#include "Utils/Helpers/Helpers.hpp"

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>

#define WEBSOCKET_PORT 2222
#define HTTP_SERVER_PORT 2223
#define HTTP_SERVER_DIRECTORY "./Menu/dist"

#define WEBSOCKET_STOP_LISTENING "stop_listening"
#define WEBSOCKET_CLOSE_MENU "close_menu"
#define WEBSOCKET_GET_ALL_SETTINGS "get_all_settings"
#define WEBSOCKET_GET_CONFIGS_LIST "get_configs_list"
#define WEBSOCKET_GET_ACTIVE_WEAPON "get_active_weapon"
#define WEBSOCKET_GET_TEAM "get_team"
#define WEBSOCKET_GET_ALL_SKINS "get_all_skins"
#define WEBSOCKET_GET_RADAR_DATA "get_radar_data"
#define WEBSOCKET_GET_MAP_NAME "get_map_name"

#define WEBSOCKET_GAME_FULL_FORCE_UPDATE "game_full_force_update"
#define WEBSOCKET_UPDATE_SETTINGS "update_settings"
#define WEBSOCKET_LOAD_CONFIG "load_config"
#define WEBSOCKET_SAVE_CONFIG "save_config"
#define WEBSOCKET_DELETE_CONFIG "delete_config"

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

struct s_radar_data {
  std::string name = "";
  int user_id = 0;
  en_team_num team_num = en_team_num::Invalid;
  bool is_fake_player = false;

  int ping = 0;
  int money = 0;
  int kills = 0;
  int assists = 0;
  int deaths = 0;
  int mvps = 0;
  int score = 0;

  int competitive_ranking = 0;
  int competitive_wins = 0;

  float x = 0;
  float y = 0;
  float z = 0;
};

class c_menu_server {
public:
  typedef websocketpp::server<websocketpp::config::asio> t_server;
  typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> t_connections_list;

private:
  t_server server;
  t_connections_list connections;

  void on_open(websocketpp::connection_hdl);
  void on_message(websocketpp::connection_hdl, t_server::message_ptr);
  void on_close(websocketpp::connection_hdl);
  void log(const std::string);

public:
  c_menu_server();
  void start();
  void send_message(websocketpp::connection_hdl, std::string, jsonxx::Value);
  void send_message_all(std::string, jsonxx::Value);
  void get_active_weapon(int);
  void get_team(en_team_num);
  void get_radar_data(std::vector<s_radar_data>);
  void get_map_name(std::string);

  void stop();
  void close_menu(websocketpp::connection_hdl);
  void get_all_settings(websocketpp::connection_hdl);
  void get_configs_list(websocketpp::connection_hdl);
  void get_active_weapon(websocketpp::connection_hdl);
  void update_settings(websocketpp::connection_hdl, jsonxx::Object);
  void load_config(websocketpp::connection_hdl, jsonxx::Object);
  void save_config(websocketpp::connection_hdl, jsonxx::Object);
  void delete_config(websocketpp::connection_hdl, jsonxx::Object);
  void game_full_force_update(websocketpp::connection_hdl);
  void get_all_skins(websocketpp::connection_hdl);
  void get_team(websocketpp::connection_hdl);
  void get_map_name(websocketpp::connection_hdl);
};

extern c_menu_server g_menu_server;