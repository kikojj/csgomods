#include "MenuServer.hpp"

void c_menu_server::stop(){
  curlpp::Cleanup my_cleanup;
  std::ostringstream os;
  os << curlpp::options::Url(std::string("http://localhost:") + std::to_string(HTTP_SERVER_PORT) + std::string("/exit"));

  server.stop_listening();
  server.stop();
  g_b_working = false;
}

void c_menu_server::close_menu(websocketpp::connection_hdl){
  if (g_engine.is_overlay_active()) {
    c_helpers::toggle_steam_overlay();
  }
}

void c_menu_server::get_all_settings(websocketpp::connection_hdl hdl){
  send_message(hdl, WEBSOCKET_GET_ALL_SETTINGS, c_settings::to_jsonxx_object(false));
}

void c_menu_server::get_configs_list(websocketpp::connection_hdl hdl){
  jsonxx::Object js_obj;
  js_obj << "files" << c_settings::get_files_list_as_jsonxx_array();
  send_message(hdl, WEBSOCKET_GET_CONFIGS_LIST, js_obj);
}

void c_menu_server::get_active_weapon(websocketpp::connection_hdl hdl){
  if (
    g_engine.client_state->state() != en_client_states::InGame ||
    g_client.local_player->m_i_health() <= 0 ||
    g_client.local_player->team_num() == en_team_num::Invalid
   ) {
    return;
  }

  c_base_weapon active_weapon = c_base_weapon(g_client.local_player->active_weapon());
  auto active_weapon_item_di = active_weapon.m_i_item_definition_index();

  if (active_weapon_item_di == (int)c_item::en_defenition_index::Invalid) {
    return;
  }

  get_active_weapon((int)active_weapon_item_di);
}

void c_menu_server::get_active_weapon(int active_weapon){
  jsonxx::Object js_obj;
  js_obj << "active_weapon" << active_weapon;
  send_message_all(WEBSOCKET_GET_ACTIVE_WEAPON, js_obj);
}

void c_menu_server::get_team(websocketpp::connection_hdl hdl) {
  if (
    g_engine.client_state->state() != en_client_states::InGame ||
    g_client.local_player->m_i_health() <= 0 ||
    g_client.local_player->team_num() == en_team_num::Invalid
    ) {
    return;
  }

  get_team(g_client.local_player->team_num());
}

void c_menu_server::get_map_name(websocketpp::connection_hdl hdl){
  auto map_dir = g_engine.client_state->map_directory().data();
  send_message(hdl, WEBSOCKET_GET_MAP_NAME, std::string(map_dir));
}

void c_menu_server::get_team(en_team_num team){
  jsonxx::Object js_obj;
  js_obj << "team" << (int)team;
  send_message_all(WEBSOCKET_GET_TEAM, js_obj);
}

void c_menu_server::get_radar_data(std::vector<s_radar_data> radar_data){
  jsonxx::Array js_arr_data;

  for (auto data : radar_data) {
    jsonxx::Object js_obj;
    js_obj
      << "name" << data.name
      << "user_id" << data.user_id
      << "team_num" << (int)data.team_num
      << "is_fake_player" << data.is_fake_player
      << "ping" << data.ping
      << "money" << data.money
      << "kills" << data.kills
      << "assists" << data.assists
      << "deaths" << data.deaths
      << "mvps" << data.mvps
      << "score" << data.score
      << "competitive_ranking" << data.competitive_ranking
      << "competitive_wins" << data.competitive_wins
      << "x" << data.x
      << "y" << data.y
      << "z" << data.z;
    js_arr_data.append(js_obj);
  }

  send_message_all(WEBSOCKET_GET_RADAR_DATA, js_arr_data);
}

void c_menu_server::get_map_name(std::string name){
  send_message_all(WEBSOCKET_GET_MAP_NAME, name);
}

void c_menu_server::update_settings(websocketpp::connection_hdl hdl, jsonxx::Object message){
  for (auto prop : message.kv_map()) {
    c_settings::set_value(prop.first, prop.second, false);
  }
}

void c_menu_server::load_config(websocketpp::connection_hdl hdl, jsonxx::Object message){
  auto fileName = message.get<jsonxx::String>("file_name");
  c_settings::get_from_file(fileName);
}

void c_menu_server::save_config(websocketpp::connection_hdl hdl, jsonxx::Object message){
  auto file_name = message.get<jsonxx::String>("file_name");
  c_settings::save_to_file(file_name + ".json");
}

void c_menu_server::delete_config(websocketpp::connection_hdl hdl, jsonxx::Object message){
  auto file_name = message.get<jsonxx::String>("file_name");
  c_settings::delete_file(file_name);
}

void c_menu_server::game_full_force_update(websocketpp::connection_hdl){
  c_helpers::full_force_update();
}

void c_menu_server::get_all_skins(websocketpp::connection_hdl hdl){
  std::fstream skins_json("Utils/skins.json");
  std::string skins_buffer((std::istreambuf_iterator<char>(skins_json)), std::istreambuf_iterator<char>());
  jsonxx::Object js_obj_skins;
  js_obj_skins.parse(skins_buffer);
  send_message(hdl, WEBSOCKET_GET_ALL_SKINS, js_obj_skins);
}


void c_menu_server::on_message(websocketpp::connection_hdl hdl, t_server::message_ptr msg) {
  try {
    jsonxx::Object data;
    data.parse(msg->get_payload());

    if (data.has<jsonxx::String>("type")) {
      auto type = data.get<jsonxx::String>("type");

      if (type == WEBSOCKET_STOP_LISTENING) {
        stop();
        return;
      }
      else if (type == WEBSOCKET_GET_CONFIGS_LIST) {
        get_configs_list(hdl);
        return;
      }
      else if (type == WEBSOCKET_CLOSE_MENU) {
        close_menu(hdl);
        return;
      }
      else if (type == WEBSOCKET_GET_ACTIVE_WEAPON) {
        get_active_weapon(hdl);
        return;
      }
      else if (type == WEBSOCKET_GAME_FULL_FORCE_UPDATE) {
        game_full_force_update(hdl);
        return;
      }
      else if (type == WEBSOCKET_GET_ALL_SKINS) {
        get_all_skins(hdl);
        return;
      }

      if (data.has<jsonxx::Object>("message")) {
        auto message = data.get<jsonxx::Object>("message");

        if (type == WEBSOCKET_UPDATE_SETTINGS) {
          update_settings(hdl, message);
          return;
        }
        else if (type == WEBSOCKET_LOAD_CONFIG && message.has<jsonxx::String>("file_name")) {
          load_config(hdl, message);
          get_all_settings(hdl);
          return;
        }
        else if (type == WEBSOCKET_SAVE_CONFIG && message.has<jsonxx::String>("file_name")) {
          save_config(hdl, message);
          get_configs_list(hdl);
          return;
        }
        else if (type == WEBSOCKET_DELETE_CONFIG && message.has<jsonxx::String>("file_name")) {
          delete_config(hdl, message);
          get_configs_list(hdl);
          return;
        }
      }
    }
  }
  catch (const std::exception& e) {
    log("onMessage error: " + (std::string)e.what());
  }
}

void c_menu_server::on_open(websocketpp::connection_hdl hdl) {
  try {
    connections.insert(hdl);
    get_all_settings(hdl);
    get_all_skins(hdl);
    get_active_weapon(hdl);
    get_team(hdl);
    get_map_name(hdl);
  }
  catch (const std::exception& e) {
    log("on_open error: " + (std::string)e.what());
  }
}

void c_menu_server::on_close(websocketpp::connection_hdl hdl) {
  try {
    connections.erase(hdl);
  }
  catch (const std::exception& e) {
    log("on_close error: " + (std::string)e.what());
  }
}

void c_menu_server::log(const std::string text) {
  std::cout << "[Websocket server]: " + text << std::endl;
}


c_menu_server::c_menu_server(){
  try {
    // Set logging settings
    server.set_access_channels(websocketpp::log::alevel::none);
    server.set_error_channels(websocketpp::log::alevel::none);

    server.init_asio();
    
    server.set_open_handler(bind(&c_menu_server::on_open, this, ::_1));
    server.set_message_handler(bind(&c_menu_server::on_message, this, ::_1, ::_2));
    server.set_close_handler(bind(&c_menu_server::on_close, this, ::_1));
  }
  catch (const std::exception& e) {
    log("constructor error: " + (std::string)e.what());
  }
}

void c_menu_server::start() {
  try {
    std::thread th_socket_server([this]() {
      server.listen(WEBSOCKET_PORT);
      server.start_accept();
      server.run();
    });

    std::thread th_http_server([]() {
      std::string command = "node ./menu/server.js port=" + std::to_string(HTTP_SERVER_PORT) + " dir=\"" + HTTP_SERVER_DIRECTORY + "\"";
      system(command.c_str());
    });

    th_socket_server.join();
    th_http_server.join();
  }
  catch (const std::exception& e) {
    log("start error: " + (std::string)e.what());
  }
}

void c_menu_server::send_message(websocketpp::connection_hdl hdl, std::string type, jsonxx::Value message){
  try {
    jsonxx::Object req;
    req << "type" << type << "message" << message;

    server.send(hdl, req.json(), websocketpp::frame::opcode::text);
  }
  catch (websocketpp::exception const& e) {
    log("send_message error: " + (std::string)e.what());
  }
}

void c_menu_server::send_message_all(std::string type, jsonxx::Value message){
  try {
    for (auto hdl : connections) {
      send_message(hdl, type, message);
    }
  }
  catch (websocketpp::exception const& e) {
    log("send_message_all error: " + (std::string)e.what());
  }
}