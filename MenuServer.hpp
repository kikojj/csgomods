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

typedef websocketpp::server<websocketpp::config::asio> Server;
typedef std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connectionsList;

struct IRadarData {
  std::string name = "";
  int userID = 0;
  TeamNum teamNum = TeamNum::Invalid;
  bool isFakePlayer = false;

  int ping = 0;
  int money = 0;
  int kills = 0;
  int assists = 0;
  int deaths = 0;
  int MVPs = 0;
  int score = 0;

  int competitiveRanking = 0;
  int competitiveWins = 0;

  float x = 0;
  float y = 0;
  float z = 0;
};

class MenuServer {
private:
  Server server;
  connectionsList connections;

  void onOpen(websocketpp::connection_hdl);
  void onMessage(websocketpp::connection_hdl, Server::message_ptr);
  void onClose(websocketpp::connection_hdl);
  void log(const std::string);

public:
  MenuServer();
  void start();
  void sendMessage(websocketpp::connection_hdl, std::string, jsonxx::Value);
  void sendMessageAll(std::string, jsonxx::Value);
  void getActiveWeapon(int);
  void getTeam(TeamNum);
  void getRadarData(std::vector<IRadarData>);
  void getMapName(std::string);

  void closeMenu(websocketpp::connection_hdl);
  void stop();
  void getAllSettings(websocketpp::connection_hdl);
  void getConfigsList(websocketpp::connection_hdl);
  void getActiveWeapon(websocketpp::connection_hdl);
  void updateSettings(websocketpp::connection_hdl, jsonxx::Object);
  void loadConfig(websocketpp::connection_hdl, jsonxx::Object);
  void saveConfig(websocketpp::connection_hdl, jsonxx::Object);
  void deleteConfig(websocketpp::connection_hdl, jsonxx::Object);
  void gameFullForceUpdate(websocketpp::connection_hdl);
  void getAllSkins(websocketpp::connection_hdl);
  void getTeam(websocketpp::connection_hdl);
  void getMapName(websocketpp::connection_hdl);
};

extern MenuServer menuServer;