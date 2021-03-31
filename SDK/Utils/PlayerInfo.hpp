#pragma once

class c_player_info {
public:
  __int64         _pad0x0;            //0x0000
  __int64         steam_id64;         //0x0008 - SteamID64
  char            name[128];          //0x0010 - Player Name
  int             user_id;            //0x0090 - Unique Server Identifier
  char            steam_id_str[20];       //0x0094 - STEAM_X:Y:Z
  char            pad_0x00A8[0x10];   //0x00A8
  unsigned long   steam_id;           //0x00B8 - SteamID 
  char            friends_names[128];
  bool            is_fake_player;
  bool            is_hltv;
  unsigned int    custom_files[4];
  unsigned char   files_downloaded;
};