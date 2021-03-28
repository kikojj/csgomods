#include "MenuServer.hpp"

void MenuServer::stopListening(websocketpp::connection_hdl hdl){
  server.stop_listening();
  server.stop();
  isWorking = false;
}

void MenuServer::closeMenu(websocketpp::connection_hdl){
  if (engine.isOverlayActive()) {
    Helpers::toggleSteamOverlay();
  }
}

void MenuServer::getAllSettings(websocketpp::connection_hdl hdl){
  sendMessage(hdl, WEBSOCKET_GET_ALL_SETTINGS, Settings::toJsonxxObject());
}

void MenuServer::getConfigsList(websocketpp::connection_hdl hdl){
  jsonxx::Object configsList;
  configsList << "files" << Settings::getFilesListAsJsonxxArray();
  sendMessage(hdl, WEBSOCKET_GET_CONFIGS_LIST, configsList);
}

void MenuServer::getActiveWeapon(websocketpp::connection_hdl hdl){
  if (
    engine.clientState->state() != ClientStates::INGAME ||
    client.localPlayer->m_iHealth() <= 0 ||
    client.localPlayer->teamNum() < TeamNum::TERRORIST
    ) {
    return;
  }

  int activeWeaponID = client.localPlayer->m_hActiveWeapon() & 0xfff;
  BaseCombatWeapon activeWeapon = BaseCombatWeapon(client.entityList->getByID(activeWeaponID - 1));
  auto activeWeaponIDI = (int)activeWeapon.m_iItemDefinitionIndex();
  if (activeWeaponIDI == (int)ItemDefinitionIndex::Invalid) {
    return;
  }

  getActiveWeapon(activeWeaponIDI);
}

void MenuServer::getActiveWeapon(int activeWeapon){
  jsonxx::Object o;
  o << "activeWeapon" << activeWeapon;
  sendMessageAll(WEBSOCKET_GET_ACTIVE_WEAPON, o);
}

void MenuServer::getTeam(websocketpp::connection_hdl hdl) {
  if (
    engine.clientState->state() != ClientStates::INGAME ||
    client.localPlayer->m_iHealth() <= 0 ||
    client.localPlayer->teamNum() < TeamNum::TERRORIST
    ) {
    return;
  }

  getTeam(client.localPlayer->teamNum());
}

void MenuServer::getMapName(websocketpp::connection_hdl hdl){
  auto mapDir = engine.clientState->mapDirectory().data();
  sendMessage(hdl, WEBSOCKET_GET_MAP_NAME, std::string(mapDir));
}

void MenuServer::getTeam(TeamNum team){
  jsonxx::Object o;
  o << "team" << (int)team;
  sendMessageAll(WEBSOCKET_GET_TEAM, o);
}

void MenuServer::getRadarData(std::vector<IRadarData> radarData){
  jsonxx::Array arrayData;

  for (auto data : radarData) {
    jsonxx::Object obj;
    obj
      << "name" << data.name
      << "userID" << data.userID
      << "teamNum" << (int)data.teamNum
      << "isFakePlayer" << data.isFakePlayer
      << "ping" << data.ping
      << "money" << data.money
      << "kills" << data.kills
      << "assists" << data.assists
      << "deaths" << data.deaths
      << "MVPs" << data.MVPs
      << "score" << data.score
      << "competitiveRanking" << data.competitiveRanking
      << "competitiveWins" << data.competitiveWins;
    arrayData.append(obj);
  }

  sendMessageAll(WEBSOCKET_GET_RADAR_DATA, arrayData);
}

void MenuServer::getMapName(std::string name){
  sendMessageAll(WEBSOCKET_GET_MAP_NAME, name);
}

void MenuServer::updateSettings(websocketpp::connection_hdl hdl, jsonxx::Object message){
  for (auto prop : message.kv_map()) {
    Settings::setValue(prop.first, prop.second);
  }
}

void MenuServer::loadConfig(websocketpp::connection_hdl hdl, jsonxx::Object message){
  auto fileName = message.get<jsonxx::String>("fileName");
  Settings::getFromFile(fileName);
}

void MenuServer::saveConfig(websocketpp::connection_hdl hdl, jsonxx::Object message){
  auto fileName = message.get<jsonxx::String>("fileName");
  Settings::saveToFile(fileName + ".json");
}

void MenuServer::deleteConfig(websocketpp::connection_hdl hdl, jsonxx::Object message){
  auto fileName = message.get<jsonxx::String>("fileName");
  Settings::deleteFile(fileName);
}

void MenuServer::gameFullForceUpdate(websocketpp::connection_hdl){
  Helpers::fullForceUpdate();
}

void MenuServer::getAllSkins(websocketpp::connection_hdl hdl){
  std::fstream skinsJson("Utils/skins.json");
  std::string skinsBuffer((std::istreambuf_iterator<char>(skinsJson)), std::istreambuf_iterator<char>());
  jsonxx::Object skins;
  skins.parse(skinsBuffer);
  sendMessage(hdl, WEBSOCKET_GET_ALL_SKINS, skins);
}


void MenuServer::onMessage(websocketpp::connection_hdl hdl, Server::message_ptr msg) {
  try {
    jsonxx::Object data;
    data.parse(msg->get_payload());

    if (data.has<jsonxx::String>("type")) {
      auto type = data.get<jsonxx::String>("type");

      if (type == WEBSOCKET_STOP_LISTENING) {
        stopListening(hdl);
        return;
      }
      else if (type == WEBSOCKET_GET_CONFIGS_LIST) {
        getConfigsList(hdl);
        return;
      }
      else if (type == WEBSOCKET_CLOSE_MENU) {
        closeMenu(hdl);
        return;
      }
      else if (type == WEBSOCKET_GET_ACTIVE_WEAPON) {
        getActiveWeapon(hdl);
        return;
      }
      else if (type == WEBSOCKET_GAME_FULL_FORCE_UPDATE) {
        gameFullForceUpdate(hdl);
        return;
      }
      else if (type == WEBSOCKET_GET_ALL_SKINS) {
        getAllSkins(hdl);
        return;
      }

      if (data.has<jsonxx::Object>("message")) {
        auto message = data.get<jsonxx::Object>("message");

        if (type == WEBSOCKET_UPDATE_SETTINGS) {
          updateSettings(hdl, message);
          return;
        }
        else if (type == WEBSOCKET_LOAD_CONFIG && message.has<jsonxx::String>("fileName")) {
          loadConfig(hdl, message);
          getAllSettings(hdl);
          return;
        }
        else if (type == WEBSOCKET_SAVE_CONFIG && message.has<jsonxx::String>("fileName")) {
          saveConfig(hdl, message);
          getConfigsList(hdl);
          return;
        }
        else if (type == WEBSOCKET_DELETE_CONFIG && message.has<jsonxx::String>("fileName")) {
          deleteConfig(hdl, message);
          getConfigsList(hdl);
          return;
        }
      }
    }
  }
  catch (const std::exception& e) {
    log("onMessage error: " + (std::string)e.what());
  }
}

void MenuServer::onOpen(websocketpp::connection_hdl hdl) {
  try {
    connections.insert(hdl);
    getAllSettings(hdl);
    getAllSkins(hdl);
    getActiveWeapon(hdl);
    getTeam(hdl);
    getMapName(hdl);
  }
  catch (const std::exception& e) {
    log("onOpen error: " + (std::string)e.what());
  }
}

void MenuServer::onClose(websocketpp::connection_hdl hdl) {
  try {
    connections.erase(hdl);
  }
  catch (const std::exception& e) {
    log("onClose error: " + (std::string)e.what());
  }
}

void MenuServer::log(const std::string text) {
  std::cout << "[Websocket server]: " + text << std::endl;
}


MenuServer::MenuServer(){
  try {
    // Set logging settings
    server.set_access_channels(websocketpp::log::alevel::none);
    server.set_error_channels(websocketpp::log::alevel::none);

    server.init_asio();
    
    server.set_open_handler(bind(&MenuServer::onOpen, this, ::_1));
    server.set_message_handler(bind(&MenuServer::onMessage, this, ::_1, ::_2));
    server.set_close_handler(bind(&MenuServer::onClose, this, ::_1));
  }
  catch (const std::exception& e) {
    log("constructor error: " + (std::string)e.what());
  }
}

void MenuServer::start() {
  try {
    std::thread thSocketServer([this]() {
      server.listen(WEBSOCKET_PORT);
      server.start_accept();
      server.run();
    });

    std::thread thHttpSrver([]() {
      std::string command = "node ./menu/server.js port=" + std::to_string(HTTP_SERVER_PORT) + " dir=\"" + HTTP_SERVER_DIRECTORY + "\"";
      system(command.c_str());
    });

    thSocketServer.join();
    thHttpSrver.join();
  }
  catch (const std::exception& e) {
    log("start error: " + (std::string)e.what());
  }
}

void MenuServer::sendMessage(websocketpp::connection_hdl hdl, std::string type, jsonxx::Value message){
  try {
    jsonxx::Object req;
    req << "type" << type << "message" << message;

    server.send(hdl, req.json(), websocketpp::frame::opcode::text);
  }
  catch (websocketpp::exception const& e) {
    log("sendMessage error: " + (std::string)e.what());
  }
}

void MenuServer::sendMessageAll(std::string type, jsonxx::Value message){
  try {
    for (auto hdl : connections) {
      sendMessage(hdl, type, message);
    }
  }
  catch (websocketpp::exception const& e) {
    log("sendMessageAll error: " + (std::string)e.what());
  }
}