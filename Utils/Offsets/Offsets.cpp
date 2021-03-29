#include "Offsets.hpp"

#pragma region netvars
int Offsets::netvars::m_ArmorValue;
int Offsets::netvars::m_Collision;
int Offsets::netvars::m_CollisionGroup;
int Offsets::netvars::m_Local;
int Offsets::netvars::m_MoveType;
int Offsets::netvars::m_OriginalOwnerXuidHigh;
int Offsets::netvars::m_OriginalOwnerXuidLow;
int Offsets::netvars::m_aimPunchAngle;
int Offsets::netvars::m_aimPunchAngleVel;
int Offsets::netvars::m_bGunGameImmunity;
int Offsets::netvars::m_bHasDefuser;
int Offsets::netvars::m_bHasHelmet;
int Offsets::netvars::m_bInReload;
int Offsets::netvars::m_bIsDefusing;
int Offsets::netvars::m_bIsScoped;
int Offsets::netvars::m_bSpotted;
int Offsets::netvars::m_bSpottedByMask;
int Offsets::netvars::m_dwBoneMatrix;
int Offsets::netvars::m_dwInGame;
int Offsets::netvars::m_fAccuracyPenalty;
int Offsets::netvars::m_fFlags;
int Offsets::netvars::m_flFallbackWear;
int Offsets::netvars::m_flFlashDuration;
int Offsets::netvars::m_flFlashMaxAlpha;
int Offsets::netvars::m_flFlashAlpha;
int Offsets::netvars::m_flNextPrimaryAttack;
int Offsets::netvars::m_hActiveWeapon;
int Offsets::netvars::m_hMyWeapons;
int Offsets::netvars::m_hObserverTarget;
int Offsets::netvars::m_hOwner;
int Offsets::netvars::m_hOwnerEntity;
int Offsets::netvars::m_iAccountID;
int Offsets::netvars::m_iAccount;
int Offsets::netvars::m_iClip1;
int Offsets::netvars::m_iCompetitiveRanking;
int Offsets::netvars::m_iCompetitiveWins;
int Offsets::netvars::m_iPing;
int Offsets::netvars::m_iKills;
int Offsets::netvars::m_iAssists;
int Offsets::netvars::m_iDeaths;
int Offsets::netvars::m_iMVPs;
int Offsets::netvars::m_iScore;
int Offsets::netvars::m_szClan;
int Offsets::netvars::m_iCrosshairId;
int Offsets::netvars::m_iEntityQuality;
int Offsets::netvars::m_iFOVStart;
int Offsets::netvars::m_iGlowIndex;
int Offsets::netvars::m_iHealth;
int Offsets::netvars::m_hViewModel;
int Offsets::netvars::m_iViewModelIndex;
int Offsets::netvars::m_nModelIndex;
int Offsets::netvars::m_iItemDefinitionIndex;
int Offsets::netvars::m_iItemIDHigh;
int Offsets::netvars::m_iObserverMode;
int Offsets::netvars::m_iShotsFired;
int Offsets::netvars::m_iState;
int Offsets::netvars::m_iTeamNum;
int Offsets::netvars::m_lifeState;
int Offsets::netvars::m_nFallbackPaintKit;
int Offsets::netvars::m_nFallbackSeed;
int Offsets::netvars::m_nFallbackStatTrak;
int Offsets::netvars::m_iDefaultFOV;
int Offsets::netvars::m_nForceBone;
int Offsets::netvars::m_nTickBase;
int Offsets::netvars::m_rgflCoordinateFrame;
int Offsets::netvars::m_szCustomName;
int Offsets::netvars::m_szLastPlaceName;
int Offsets::netvars::m_vecOrigin;
int Offsets::netvars::m_vecVelocity;
int Offsets::netvars::m_vecViewOffset;
int Offsets::netvars::m_viewPunchAngle;
int Offsets::netvars::m_thirdPersonViewAngles;
int Offsets::netvars::m_clrRender;
int Offsets::netvars::m_flC4Blow;
int Offsets::netvars::m_flTimerLength;
int Offsets::netvars::m_flDefuseLength;
int Offsets::netvars::m_flDefuseCountDown;
int Offsets::netvars::m_hBombDefuser;
int Offsets::netvars::m_nBombSite;
int Offsets::netvars::cs_gamerules_data;
int Offsets::netvars::m_SurvivalRules;
int Offsets::netvars::m_SurvivalGameRuleDecisionTypes;
int Offsets::netvars::m_bIsValveDS;
int Offsets::netvars::m_bFreezePeriod;
int Offsets::netvars::m_bWarmupPeriod;
int Offsets::netvars::m_bBombPlanted;
int Offsets::netvars::m_bIsQueuedMatchmaking;
int Offsets::netvars::m_flSimulationTime;
int Offsets::netvars::m_flLowerBodyYawTarget;
int Offsets::netvars::m_angEyeAnglesX;
int Offsets::netvars::m_angEyeAnglesY;
int Offsets::netvars::m_flNextAttack;
int Offsets::netvars::m_iMostRecentModelBoneCounter;
int Offsets::netvars::m_flLastBoneSetupTime;
int Offsets::netvars::m_bStartedArming;
int Offsets::netvars::m_bUseCustomBloomScale;
int Offsets::netvars::m_bUseCustomAutoExposureMin;
int Offsets::netvars::m_bUseCustomAutoExposureMax;
int Offsets::netvars::m_flCustomBloomScale;
int Offsets::netvars::m_flCustomAutoExposureMin;
int Offsets::netvars::m_flCustomAutoExposureMax;
int Offsets::netvars::m_hWeaponWorldModel;
int Offsets::netvars::m_bDormant;
#pragma endregion

#pragma region signatures
int Offsets::signatures::dwClientState;
int Offsets::signatures::dwModelPrecache;
int Offsets::signatures::dwClientState_GetLocalPlayer;
int Offsets::signatures::dwClientState_IsHLTV;
int Offsets::signatures::dwClientState_Map;
int Offsets::signatures::dwClientState_MapDirectory;
int Offsets::signatures::dwClientState_MaxPlayer;
int Offsets::signatures::dwClientState_PlayerInfo;
int Offsets::signatures::dwClientState_State;
int Offsets::signatures::dwClientState_ViewAngles;
int Offsets::signatures::clientstate_delta_ticks;
int Offsets::signatures::clientstate_last_outgoing_command;
int Offsets::signatures::clientstate_choked_commands;
int Offsets::signatures::clientstate_net_channel;
int Offsets::signatures::dwEntityList;
int Offsets::signatures::dwForceAttack;
int Offsets::signatures::dwForceAttack2;
int Offsets::signatures::dwForceBackward;
int Offsets::signatures::dwForceForward;
int Offsets::signatures::dwForceJump;
int Offsets::signatures::dwForceLeft;
int Offsets::signatures::dwForceRight;
int Offsets::signatures::dwGameDir;
int Offsets::signatures::dwGameRulesProxy;
int Offsets::signatures::dwGetAllClasses;
int Offsets::signatures::dwGlowObjectManager;
int Offsets::signatures::dwInput;
int Offsets::signatures::dwInterfaceLinkList;
int Offsets::signatures::dwLocalPlayer;
int Offsets::signatures::dwMouseEnable;
int Offsets::signatures::dwMouseEnablePtr;
int Offsets::signatures::dwPlayerResource;
int Offsets::signatures::dwRadarBase;
int Offsets::signatures::dwSensitivity;
int Offsets::signatures::dwSensitivityPtr;
int Offsets::signatures::dwSetClanTag;
int Offsets::signatures::dwViewMatrix;
int Offsets::signatures::dwWeaponTable;
int Offsets::signatures::dwWeaponTableIndex;
int Offsets::signatures::dwYawPtr;
int Offsets::signatures::dwZoomSensitivityRatioPtr;
int Offsets::signatures::dwbSendPackets;
int Offsets::signatures::dwppDirect3DDevice9;
int Offsets::signatures::m_pStudioHdr;
int Offsets::signatures::m_yawClassPtr;
int Offsets::signatures::m_pitchClassPtr;
int Offsets::signatures::interface_engine_cvar;
int Offsets::signatures::convar_name_hash_table;
int Offsets::signatures::model_ambient_min;
int Offsets::signatures::set_abs_angles;
int Offsets::signatures::set_abs_origin;
int Offsets::signatures::is_c4_owner;
int Offsets::signatures::force_update_spectator_glow;
int Offsets::signatures::anim_overlays;
int Offsets::signatures::m_flSpawnTime;
int Offsets::signatures::find_hud_element;
int Offsets::signatures::overlayActivated1;
int Offsets::signatures::overlayActivated2;
int Offsets::signatures::hConfirmMatch;
int Offsets::signatures::dwClientMode;
int Offsets::signatures::dwTraceLine;
int Offsets::signatures::dwLineThroughSmoke;
int Offsets::signatures::dwClientCmdUD;
int Offsets::signatures::dwGlobalVars;
int Offsets::signatures::dwRankReveal;
#pragma endregion

void Offsets::initNetvars(){
  Offsets::netvars::m_bDormant = 0xED;

  //DT_BaseEntity
  Offsets::netvars::m_bSpotted        = Scanner::getNetvar("m_bSpotted",       "m_bSpotted",       "DT_BaseEntity");
  Offsets::netvars::m_bSpottedByMask  = Scanner::getNetvar("m_bSpottedByMask", "m_bSpottedByMask", "DT_BaseEntity");
  Offsets::netvars::m_vecOrigin       = Scanner::getNetvar("m_vecOrigin",      "m_vecOrigin",      "DT_BaseEntity");

  //DT_CSPlayer
  Offsets::netvars::m_ArmorValue                  = Scanner::getNetvar("m_ArmorValue",                   "m_ArmorValue",           "DT_CSPlayer");
  Offsets::netvars::m_CollisionGroup              = Scanner::getNetvar("m_CollisionGroup",               "m_CollisionGroup",       "DT_CSPlayer");
  Offsets::netvars::m_MoveType                    = Scanner::getNetvar("m_MoveType",                     "m_nRenderMode",          "DT_CSPlayer", 1);
  Offsets::netvars::m_bGunGameImmunity            = Scanner::getNetvar("m_bGunGameImmunity",             "m_bGunGameImmunity",     "DT_CSPlayer");
  Offsets::netvars::m_bHasDefuser                 = Scanner::getNetvar("m_bHasDefuser",                  "m_bHasDefuser",          "DT_CSPlayer");
  Offsets::netvars::m_bHasHelmet                  = Scanner::getNetvar("m_bHasHelmet",                   "m_bHasHelmet",           "DT_CSPlayer");
  Offsets::netvars::m_bIsDefusing                 = Scanner::getNetvar("m_bIsDefusing",                  "m_bIsDefusing",          "DT_CSPlayer");
  Offsets::netvars::m_bIsScoped                   = Scanner::getNetvar("m_bIsScoped",                    "m_bIsScoped",            "DT_CSPlayer");
  Offsets::netvars::m_fFlags                      = Scanner::getNetvar("m_fFlags",                       "m_fFlags",               "DT_CSPlayer");
  Offsets::netvars::m_flFlashDuration             = Scanner::getNetvar("m_flFlashDuration",              "m_flFlashDuration",      "DT_CSPlayer");
  Offsets::netvars::m_flFlashAlpha                = Scanner::getNetvar("m_flFlashAlpha",                 "m_flFlashAlpha",         "DT_CSPlayer");
  Offsets::netvars::m_flFlashMaxAlpha             = Scanner::getNetvar("m_flFlashMaxAlpha",              "m_flFlashMaxAlpha",      "DT_CSPlayer");
  Offsets::netvars::m_hOwnerEntity                = Scanner::getNetvar("m_hOwnerEntity",                 "m_hOwnerEntity",         "DT_CSPlayer");
  Offsets::netvars::m_iCrosshairId                = Scanner::getNetvar("m_iCrosshairId",                 "m_bHasDefuser",          "DT_CSPlayer", 92);
  Offsets::netvars::m_iFOVStart                   = Scanner::getNetvar("m_iFOVStart",                    "m_iFOVStart",            "DT_CSPlayer");
  Offsets::netvars::m_iGlowIndex                  = Scanner::getNetvar("m_iGlowIndex",                   "m_flFlashDuration",      "DT_CSPlayer", 24);
  Offsets::netvars::m_iShotsFired                 = Scanner::getNetvar("m_iShotsFired",                  "m_iShotsFired",          "DT_CSPlayer");
  Offsets::netvars::m_lifeState                   = Scanner::getNetvar("m_lifeState",                    "m_lifeState",            "DT_CSPlayer");
  Offsets::netvars::m_iDefaultFOV                 = Scanner::getNetvar("m_iDefaultFOV",                  "m_iDefaultFOV",          "DT_CSPlayer");
  Offsets::netvars::m_rgflCoordinateFrame         = Scanner::getNetvar("m_rgflCoordinateFrame",          "m_CollisionGroup",       "DT_CSPlayer", -48);
  Offsets::netvars::m_szLastPlaceName             = Scanner::getNetvar("m_szLastPlaceName",              "m_szLastPlaceName",      "DT_CSPlayer");
  Offsets::netvars::m_vecVelocity                 = Scanner::getNetvar("m_vecVelocity",                  "m_vecVelocity[0]",       "DT_CSPlayer");
  Offsets::netvars::m_vecViewOffset               = Scanner::getNetvar("m_vecViewOffset",                "m_vecViewOffset[0]",     "DT_CSPlayer");
  Offsets::netvars::m_thirdPersonViewAngles       = Scanner::getNetvar("m_thirdPersonViewAngles",        "deadflag",               "DT_CSPlayer", 4);
  Offsets::netvars::m_flSimulationTime            = Scanner::getNetvar("m_flSimulationTime",             "m_flSimulationTime",     "DT_CSPlayer");
  Offsets::netvars::m_flLowerBodyYawTarget        = Scanner::getNetvar("m_flLowerBodyYawTarget",         "m_flLowerBodyYawTarget", "DT_CSPlayer");
  Offsets::netvars::m_angEyeAnglesX               = Scanner::getNetvar("m_angEyeAngles",                 "m_angEyeAngles[0]",      "DT_CSPlayer");
  Offsets::netvars::m_angEyeAnglesY               = Scanner::getNetvar("m_angEyeAngles",                 "m_angEyeAngles[1]",      "DT_CSPlayer");
  Offsets::netvars::m_flNextAttack                = Scanner::getNetvar("m_flNextAttack",                 "m_flNextAttack",         "DT_CSPlayer");
  Offsets::netvars::m_iMostRecentModelBoneCounter = Scanner::getNetvar("m_iMostRecentModelBoneCounter",  "m_nForceBone",           "DT_CSPlayer", 4);
  Offsets::netvars::m_iAccount                    = Scanner::getNetvar("m_iAccount",                     "m_iAccount",             "DT_CSPlayer");

  //DT_BasePlayer
  Offsets::netvars::m_Collision         = Scanner::getNetvar("m_Collision",        "m_Collision",        "DT_BasePlayer");
  Offsets::netvars::m_Local             = Scanner::getNetvar("m_Local",            "m_Local",            "DT_BasePlayer");
  Offsets::netvars::m_aimPunchAngle     = Scanner::getNetvar("m_aimPunchAngle",    "m_aimPunchAngle",    "DT_BasePlayer");
  Offsets::netvars::m_aimPunchAngleVel  = Scanner::getNetvar("m_aimPunchAngleVel", "m_aimPunchAngleVel", "DT_BasePlayer");
  Offsets::netvars::m_hActiveWeapon     = Scanner::getNetvar("m_hActiveWeapon",    "m_hActiveWeapon",    "DT_BasePlayer");
  Offsets::netvars::m_hMyWeapons        = Scanner::getNetvar("m_hMyWeapons",       "m_hActiveWeapon",    "DT_BasePlayer", -256);
  Offsets::netvars::m_hObserverTarget   = Scanner::getNetvar("m_hObserverTarget",  "m_hObserverTarget",  "DT_BasePlayer");
  Offsets::netvars::m_iHealth           = Scanner::getNetvar("m_iHealth",          "m_iHealth",          "DT_BasePlayer");
  Offsets::netvars::m_hViewModel        = Scanner::getNetvar("m_hViewModel",       "m_hViewModel[0]",    "DT_BasePlayer");
  Offsets::netvars::m_iObserverMode     = Scanner::getNetvar("m_iObserverMode",    "m_iObserverMode",    "DT_BasePlayer");
  Offsets::netvars::m_iTeamNum          = Scanner::getNetvar("m_iTeamNum",         "m_iTeamNum",         "DT_BasePlayer");
  Offsets::netvars::m_nTickBase         = Scanner::getNetvar("m_nTickBase",        "m_nTickBase",        "DT_BasePlayer");
  Offsets::netvars::m_viewPunchAngle    = Scanner::getNetvar("m_viewPunchAngle",   "m_viewPunchAngle",   "DT_BasePlayer");
  Offsets::netvars::m_clrRender         = Scanner::getNetvar("m_clrRender",        "m_clrRender",        "DT_BaseEntity");

  //DT_BaseCombatWeapon
  Offsets::netvars::m_bInReload             = Scanner::getNetvar("m_bInReload",            "m_flNextPrimaryAttack",  "DT_BaseCombatWeapon", 109);
  Offsets::netvars::m_flNextPrimaryAttack   = Scanner::getNetvar("m_flNextPrimaryAttack",  "m_flNextPrimaryAttack",  "DT_BaseCombatWeapon");
  Offsets::netvars::m_iClip1                = Scanner::getNetvar("m_iClip1",               "m_iClip1",               "DT_BaseCombatWeapon");
  Offsets::netvars::m_iViewModelIndex       = Scanner::getNetvar("m_iViewModelIndex",      "m_iViewModelIndex",      "DT_BaseCombatWeapon");
  Offsets::netvars::m_iItemDefinitionIndex  = Scanner::getNetvar("m_iItemDefinitionIndex", "m_iItemDefinitionIndex", "DT_BaseCombatWeapon");
  Offsets::netvars::m_iState                = Scanner::getNetvar("m_iState",               "m_iState",               "DT_BaseCombatWeapon");
  Offsets::netvars::m_hWeaponWorldModel     = Scanner::getNetvar("m_hWeaponWorldModel",    "m_hWeaponWorldModel",    "DT_BaseCombatWeapon");

  //DT_WeaponCSBase
  Offsets::netvars::m_fAccuracyPenalty = Scanner::getNetvar("m_fAccuracyPenalty", "m_fAccuracyPenalty", "DT_WeaponCSBase");

  //DT_PlantedC4
  Offsets::netvars::m_flC4Blow          = Scanner::getNetvar("m_flC4Blow",           "m_flC4Blow",           "DT_PlantedC4");
  Offsets::netvars::m_flTimerLength     = Scanner::getNetvar("m_flTimerLength",      "m_flTimerLength",      "DT_PlantedC4");
  Offsets::netvars::m_flDefuseLength    = Scanner::getNetvar("m_flDefuseLength",     "m_flDefuseLength",     "DT_PlantedC4");
  Offsets::netvars::m_flDefuseCountDown = Scanner::getNetvar("m_flDefuseCountDown",  "m_flDefuseCountDown",  "DT_PlantedC4");
  Offsets::netvars::m_hBombDefuser      = Scanner::getNetvar("m_hBombDefuser",       "m_hBombDefuser",       "DT_PlantedC4");
  Offsets::netvars::m_nBombSite         = Scanner::getNetvar("m_nBombSite",          "m_nBombSite",          "DT_PlantedC4");

  //DT_WeaponC4
  Offsets::netvars::m_bStartedArming = Scanner::getNetvar("m_bStartedArming", "m_bStartedArming", "DT_WeaponC4");

  //DT_BaseAttributableItem
  Offsets::netvars::m_OriginalOwnerXuidHigh   = Scanner::getNetvar("m_OriginalOwnerXuidHigh",  "m_OriginalOwnerXuidHigh",  "DT_BaseAttributableItem");
  Offsets::netvars::m_OriginalOwnerXuidLow    = Scanner::getNetvar("m_OriginalOwnerXuidLow",   "m_OriginalOwnerXuidLow",   "DT_BaseAttributableItem");
  Offsets::netvars::m_flFallbackWear          = Scanner::getNetvar("m_flFallbackWear",         "m_flFallbackWear",         "DT_BaseAttributableItem");
  Offsets::netvars::m_iAccountID              = Scanner::getNetvar("m_iAccountID",             "m_iAccountID",             "DT_BaseAttributableItem");
  Offsets::netvars::m_iEntityQuality          = Scanner::getNetvar("m_iEntityQuality",         "m_iEntityQuality",         "DT_BaseAttributableItem");
  Offsets::netvars::m_iItemIDHigh             = Scanner::getNetvar("m_iItemIDHigh",            "m_iItemIDHigh",            "DT_BaseAttributableItem");
  Offsets::netvars::m_nFallbackPaintKit       = Scanner::getNetvar("m_nFallbackPaintKit",      "m_nFallbackPaintKit",      "DT_BaseAttributableItem");
  Offsets::netvars::m_nFallbackSeed           = Scanner::getNetvar("m_nFallbackSeed",          "m_nFallbackSeed",          "DT_BaseAttributableItem");
  Offsets::netvars::m_nFallbackStatTrak       = Scanner::getNetvar("m_nFallbackStatTrak",      "m_nFallbackStatTrak",      "DT_BaseAttributableItem");
  Offsets::netvars::m_szCustomName            = Scanner::getNetvar("m_szCustomName",           "m_szCustomName",           "DT_BaseAttributableItem");

  //DT_BaseAnimating
  Offsets::netvars::m_dwBoneMatrix        = Scanner::getNetvar("m_dwBoneMatrix",         "m_nForceBone", "DT_BaseAnimating", 28);
  Offsets::netvars::m_dwInGame            = Scanner::getNetvar("m_dwInGame",             "m_dwInGame",   "DT_BaseAnimating");
  Offsets::netvars::m_nForceBone          = Scanner::getNetvar("m_nForceBone",           "m_nForceBone", "DT_BaseAnimating");
  Offsets::netvars::m_flLastBoneSetupTime = Scanner::getNetvar("m_flLastBoneSetupTime",  "m_nSequence",  "DT_BaseAnimating", 104);

  //DT_PredictedViewModel
  Offsets::netvars::m_hOwner = Scanner::getNetvar("m_hOwner", "m_hOwner", "DT_PredictedViewModel");

  //DT_CSPlayerResource
  /*
  PNETVAR(int32_t, m_nActiveCoinRank, "DT_CSPlayerResource", "m_nActiveCoinRank");
  PNETVAR(int32_t, m_nMusicID, "DT_CSPlayerResource", "m_nMusicID");
  PNETVAR(int32_t, m_nPersonaDataPublicLevel, "DT_CSPlayerResource", "m_nPersonaDataPublicLevel");
  PNETVAR(int32_t, m_nPersonaDataPublicCommendsLeader, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsLeader");
  PNETVAR(int32_t, m_nPersonaDataPublicCommendsTeacher, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsTeacher");
  PNETVAR(int32_t, m_nPersonaDataPublicCommendsFriendly, "DT_CSPlayerResource", "m_nPersonaDataPublicCommendsFriendly");
  */
  Offsets::netvars::m_iCompetitiveRanking = Scanner::getNetvar("m_iCompetitiveRanking",  "m_iCompetitiveRanking",   "DT_CSPlayerResource");
  Offsets::netvars::m_iCompetitiveWins    = Scanner::getNetvar("m_iCompetitiveWins",     "m_iCompetitiveWins",      "DT_CSPlayerResource");
  Offsets::netvars::m_iPing               = Scanner::getNetvar("m_iPing",                "m_iPing",                 "DT_CSPlayerResource");
  Offsets::netvars::m_iKills              = Scanner::getNetvar("m_iKills",               "m_iKills",                "DT_CSPlayerResource");
  Offsets::netvars::m_iAssists            = Scanner::getNetvar("m_iAssists",             "m_iAssists",              "DT_CSPlayerResource");
  Offsets::netvars::m_iDeaths             = Scanner::getNetvar("m_iDeaths",              "m_iDeaths",               "DT_CSPlayerResource");
  Offsets::netvars::m_iMVPs               = Scanner::getNetvar("m_iMVPs",                "m_iMVPs",                 "DT_CSPlayerResource");
  Offsets::netvars::m_iScore              = Scanner::getNetvar("m_iScore",               "m_iScore",                "DT_CSPlayerResource");
  Offsets::netvars::m_szClan              = Scanner::getNetvar("m_szClan",               "m_szClan",                "DT_CSPlayerResource");
  
  //DT_BaseViewModel
  Offsets::netvars::m_nModelIndex = Scanner::getNetvar("m_nModelIndex", "m_nModelIndex", "DT_BaseViewModel");

  //DT_CSGameRulesProxy
  Offsets::netvars::cs_gamerules_data               = Scanner::getNetvar("cs_gamerules_data",                "cs_gamerules_data",                "DT_CSGameRulesProxy");
  Offsets::netvars::m_SurvivalRules                 = Scanner::getNetvar("m_SurvivalRules",                  "m_SurvivalRules",                  "DT_CSGameRulesProxy");
  Offsets::netvars::m_SurvivalGameRuleDecisionTypes = Scanner::getNetvar("m_SurvivalGameRuleDecisionTypes",  "m_SurvivalGameRuleDecisionTypes",  "DT_CSGameRulesProxy");
  Offsets::netvars::m_bIsValveDS                    = Scanner::getNetvar("m_bIsValveDS",                     "m_bIsValveDS",                     "DT_CSGameRulesProxy");
  Offsets::netvars::m_bFreezePeriod                 = Scanner::getNetvar("m_bFreezePeriod",                  "m_bFreezePeriod",                  "DT_CSGameRulesProxy");
  Offsets::netvars::m_bWarmupPeriod                 = Scanner::getNetvar("m_bWarmupPeriod",                  "m_bWarmupPeriod",                  "DT_CSGameRulesProxy");
  Offsets::netvars::m_bBombPlanted                  = Scanner::getNetvar("m_bBombPlanted",                   "m_bBombPlanted",                   "DT_CSGameRulesProxy");
  Offsets::netvars::m_bIsQueuedMatchmaking          = Scanner::getNetvar("m_bIsQueuedMatchmaking",           "m_bIsQueuedMatchmaking",           "DT_CSGameRulesProxy");
  
  //DT_EnvTonemapController
  Offsets::netvars::m_bUseCustomBloomScale      = Scanner::getNetvar("m_bUseCustomBloomScale",       "m_bUseCustomBloomScale",       "DT_EnvTonemapController");
  Offsets::netvars::m_bUseCustomAutoExposureMin = Scanner::getNetvar("m_bUseCustomAutoExposureMin",  "m_bUseCustomAutoExposureMin",  "DT_EnvTonemapController");
  Offsets::netvars::m_bUseCustomAutoExposureMax = Scanner::getNetvar("m_bUseCustomAutoExposureMax",  "m_bUseCustomAutoExposureMax",  "DT_EnvTonemapController");
  Offsets::netvars::m_flCustomBloomScale        = Scanner::getNetvar("m_flCustomBloomScale",         "m_flCustomBloomScale",         "DT_EnvTonemapController");
  Offsets::netvars::m_flCustomAutoExposureMin   = Scanner::getNetvar("m_flCustomAutoExposureMin",    "m_flCustomAutoExposureMin",    "DT_EnvTonemapController");
  Offsets::netvars::m_flCustomAutoExposureMax   = Scanner::getNetvar("m_flCustomAutoExposureMax",    "m_flCustomAutoExposureMax",    "DT_EnvTonemapController");
}

void Offsets::initSignatures(){
  Offsets::signatures::dwGetAllClasses = Scanner::getAllClassesSignature();

  //CLIENT_DLL_NAME
  Offsets::signatures::dwEntityList                 = Scanner::getSignature(CLIENT_DLL_NAME, "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", { 1 });
  Offsets::signatures::dwForceAttack                = Scanner::getSignature(CLIENT_DLL_NAME, "89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04", { 2 });
  Offsets::signatures::dwForceAttack2               = Scanner::getSignature(CLIENT_DLL_NAME, "89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04", { 2 }, 12);
  Offsets::signatures::dwForceBackward              = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 51 53 8A 5D 08", { 287 });
  Offsets::signatures::dwForceForward               = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 51 53 8A 5D 08", { 245 });
  Offsets::signatures::dwForceJump                  = Scanner::getSignature(CLIENT_DLL_NAME, "8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02", { 2 });
  Offsets::signatures::dwForceLeft                  = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 51 53 8A 5D 08", { 465 });
  Offsets::signatures::dwForceRight                 = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 51 53 8A 5D 08", { 512 });
  Offsets::signatures::dwGameRulesProxy             = Scanner::getSignature(CLIENT_DLL_NAME, "A1 ? ? ? ? 85 C0 0F 84 ? ? ? ? 80 B8 ? ? ? ? ? 74 7A", { 1 });
  Offsets::signatures::dwGlowObjectManager          = Scanner::getSignature(CLIENT_DLL_NAME, "A1 ? ? ? ? A8 01 75 4B", { 1 }, 4);
  Offsets::signatures::dwInput                      = Scanner::getSignature(CLIENT_DLL_NAME, "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10", { 1 });
  Offsets::signatures::dwInterfaceLinkList          = Scanner::getSignature(CLIENT_DLL_NAME, "8B 35 ? ? ? ? 57 85 F6 74 ? 8B 7D 08 8B 4E 04 8B C7 8A 11 3A 10");
  Offsets::signatures::dwLocalPlayer                = Scanner::getSignature(CLIENT_DLL_NAME, "8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF", { 3 }, 4);
  Offsets::signatures::dwMouseEnable                = Scanner::getSignature(CLIENT_DLL_NAME, "B9 ? ? ? ? FF 50 34 85 C0 75 10", { 1 }, 48);
  Offsets::signatures::dwMouseEnablePtr             = Scanner::getSignature(CLIENT_DLL_NAME, "B9 ? ? ? ? FF 50 34 85 C0 75 10", { 1 });
  Offsets::signatures::dwPlayerResource             = Scanner::getSignature(CLIENT_DLL_NAME, "8B 3D ? ? ? ? 85 FF 0F 84 ? ? ? ? 81 C7", { 2 });
  Offsets::signatures::dwRadarBase                  = Scanner::getSignature(CLIENT_DLL_NAME, "A1 ? ? ? ? 8B 0C B0 8B 01 FF 50 ? 46 3B 35 ? ? ? ? 7C EA 8B 0D", { 1 });
  Offsets::signatures::dwSensitivity                = Scanner::getSignature(CLIENT_DLL_NAME, "81 F9 ? ? ? ? 75 1D F3 0F 10 05 ? ? ? ? F3 0F 11 44 24 ? 8B 44 24 0C 35 ? ? ? ? 89 44 24 0C", { 2 }, 44);
  Offsets::signatures::dwSensitivityPtr             = Scanner::getSignature(CLIENT_DLL_NAME, "81 F9 ? ? ? ? 75 1D F3 0F 10 05 ? ? ? ? F3 0F 11 44 24 ? 8B 44 24 0C 35 ? ? ? ? 89 44 24 0C");
  Offsets::signatures::dwViewMatrix                 = Scanner::getSignature(CLIENT_DLL_NAME, "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9", { 3 }, 176);
  Offsets::signatures::dwWeaponTable                = Scanner::getSignature(CLIENT_DLL_NAME, "B9 ? ? ? ? 6A 00 FF 50 08 C3", { 1 });
  Offsets::signatures::dwWeaponTableIndex           = Scanner::getSignature(CLIENT_DLL_NAME, "39 86 ? ? ? ? 74 06 89 86 ? ? ? ? 8B 86", { 2 });
  Offsets::signatures::dwYawPtr                     = Scanner::getSignature(CLIENT_DLL_NAME, "81 F9 ? ? ? ? 75 16 F3 0F 10 05 ? ? ? ? F3 0F 11 45 ? 81 75 ? ? ? ? ? EB 0A 8B 01 8B 40 30 FF D0 D9 5D 0C 8B 55 08", { 2 });
  Offsets::signatures::dwZoomSensitivityRatioPtr    = Scanner::getSignature(CLIENT_DLL_NAME, "81 F9 ? ? ? ? 75 1A F3 0F 10 05 ? ? ? ? F3 0F 11 45 ? 8B 45 F4 35 ? ? ? ? 89 45 FC EB 0A 8B 01 8B 40 30 FF D0 D9 5D FC A1", { 2 });
  Offsets::signatures::dwppDirect3DDevice9          = Scanner::getSignature(CLIENT_DLL_NAME, "A1 ? ? ? ? 50 8B 08 FF 51 0C", { 1 });
  Offsets::signatures::m_pStudioHdr                 = Scanner::getSignature(CLIENT_DLL_NAME, "8B B6 ? ? ? ? 85 F6 74 05 83 3E 00 75 02 33 F6 F3 0F 10 44 2", { 2 });
  Offsets::signatures::m_yawClassPtr                = Scanner::getSignature(CLIENT_DLL_NAME, "81 F9 ? ? ? ? 75 16 F3 0F 10 05 ? ? ? ? F3 0F 11 45 ? 81 75 ? ? ? ? ? EB 0A 8B 01 8B 40 30 FF D0 D9 5D 0C 8B 55 08", { 2 });
  Offsets::signatures::m_pitchClassPtr              = Scanner::getSignature(CLIENT_DLL_NAME, "A1 ? ? ? ? 89 74 24 28", { 1 });
  Offsets::signatures::set_abs_angles               = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");
  Offsets::signatures::set_abs_origin               = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
  Offsets::signatures::is_c4_owner                  = Scanner::getSignature(CLIENT_DLL_NAME, "56 8B F1 85 F6 74 31");
  Offsets::signatures::force_update_spectator_glow  = Scanner::getSignature(CLIENT_DLL_NAME, "74 07 8B CB E8 ? ? ? ? 83 C7 10");
  Offsets::signatures::anim_overlays                = Scanner::getSignature(CLIENT_DLL_NAME, "8B 89 ? ? ? ? 8D 0C D1", { 2 }, 0, false);
  Offsets::signatures::m_flSpawnTime                = Scanner::getSignature(CLIENT_DLL_NAME, "89 86 ? ? ? ? E8 ? ? ? ? 80 BE ? ? ? ? ?", { 2 }, 0, false);
  Offsets::signatures::find_hud_element             = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28", {  }, 0, false);
  Offsets::signatures::hConfirmMatch                = Scanner::getSignature(CLIENT_DLL_NAME, "56 8B 35 ? ? ? ? 57 83 BE", { 0 }, -4, true, false);
  Offsets::signatures::dwClientMode                 = Scanner::getSignature(CLIENT_DLL_NAME, "8B 0D ? ? ? ? FF 75 08 8B 01 FF 50 64", { 0 }, 2, false, false);
  Offsets::signatures::dwTraceLine                  = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 83 E4 F0 83 EC 7C 56 52", {0}, 0, false, false);
  Offsets::signatures::dwLineThroughSmoke           = Scanner::getSignature(CLIENT_DLL_NAME, "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0", {0}, 0, false, false);
  Offsets::signatures::dwGlobalVars                 = Scanner::getSignature(CLIENT_DLL_NAME, "A1 ? ? ? ? 8B 4D FC 8B 40 10", { 1 }, 0, true, false);
  Offsets::signatures::dwRankReveal                 = Scanner::getSignature(CLIENT_DLL_NAME, "8D 4E 74 8B C4 C7 40 04 ? ? ? ? C7 00", { 14 }, 0, false, true);

  //ENGINE_DLL_NAME
  Offsets::signatures::dwClientState                      = Scanner::getSignature(ENGINE_DLL_NAME, "A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0", { 1 });
  Offsets::signatures::dwModelPrecache                    = Scanner::getSignature(ENGINE_DLL_NAME, "8D 44 24 3C 8B F1 50 8D 44 24 3C B9", { 0 }, 12);
  Offsets::signatures::dwClientState_GetLocalPlayer       = Scanner::getSignature(ENGINE_DLL_NAME, "8B 80 ? ? ? ? 40 C3", { 2 }, 0, false);
  Offsets::signatures::dwClientState_IsHLTV               = Scanner::getSignature(ENGINE_DLL_NAME, "80 BF ? ? ? ? ? 0F 84 ? ? ? ? 32 DB", { 2 }, 0, false);
  Offsets::signatures::dwClientState_Map                  = Scanner::getSignature(ENGINE_DLL_NAME, "05 ? ? ? ? C3 CC CC CC CC CC CC CC A1", { 1 }, 0, false);
  Offsets::signatures::dwClientState_MapDirectory         = Scanner::getSignature(ENGINE_DLL_NAME, "B8 ? ? ? ? C3 05 ? ? ? ? C3", { 7 }, 0, false);
  Offsets::signatures::dwClientState_MaxPlayer            = Scanner::getSignature(ENGINE_DLL_NAME, "A1 ? ? ? ? 8B 80 ? ? ? ? C3 CC CC CC CC 55 8B EC 8A 45 08", { 7 }, 0, false);
  Offsets::signatures::dwClientState_PlayerInfo           = Scanner::getSignature(ENGINE_DLL_NAME, "8B 89 ? ? ? ? 85 C9 0F 84 ? ? ? ? 8B 01", { 2 }, 0, false);
  Offsets::signatures::dwClientState_State                = Scanner::getSignature(ENGINE_DLL_NAME, "83 B8 ? ? ? ? ? 0F 94 C0 C3", { 2 }, 0, false);
  Offsets::signatures::dwClientState_ViewAngles           = Scanner::getSignature(ENGINE_DLL_NAME, "F3 0F 11 80 ? ? ? ? D9 46 04 D9 05", { 4 }, 0, false);
  Offsets::signatures::clientstate_delta_ticks            = Scanner::getSignature(ENGINE_DLL_NAME, "C7 87 ? ? ? ? ? ? ? ? FF 15 ? ? ? ? 83 C4 08", { 2 }, 0, false);
  Offsets::signatures::clientstate_last_outgoing_command  = Scanner::getSignature(ENGINE_DLL_NAME, "8B 8F ? ? ? ? 8B 87 ? ? ? ? 41", { 2 }, 0, false);
  Offsets::signatures::clientstate_choked_commands        = Scanner::getSignature(ENGINE_DLL_NAME, "8B 87 ? ? ? ? 41", { 2 }, 0, false);
  Offsets::signatures::clientstate_net_channel            = Scanner::getSignature(ENGINE_DLL_NAME, "8B 8F ? ? ? ? 8B 01 8B 40 18", { 2 }, 0, false);
  Offsets::signatures::dwSetClanTag                       = Scanner::getSignature(ENGINE_DLL_NAME, "53 56 57 8B DA 8B F9 FF 15");
  Offsets::signatures::dwbSendPackets                     = Scanner::getSignature(ENGINE_DLL_NAME, "B3 01 8B 01 8B 40 10 FF D0 84 C0 74 0F 80 BF ? ? ? ? ? 0F 84", { 0 }, 1);
  Offsets::signatures::model_ambient_min                  = Scanner::getSignature(ENGINE_DLL_NAME, "F3 0F 10 0D ? ? ? ? F3 0F 11 4C 24 ? 8B 44 24 20 35 ? ? ? ? 89 44 24 0C", { 4 });
  Offsets::signatures::overlayActivated1                  = Scanner::getSignature(ENGINE_DLL_NAME, "50 51 8D 85 ? ? ? ? B9", { 9 });
  Offsets::signatures::overlayActivated2                  = Scanner::getSignature(ENGINE_DLL_NAME, "88 86 ? ? 00 00 5E 84", { 2 });
  Offsets::signatures::dwGameDir                          = Scanner::getSignature(ENGINE_DLL_NAME, "68 ? ? ? ? 8D 85 ? ? ? ? 50 68 ? ? ? ? 68", { 1 });
  Offsets::signatures::dwClientCmdUD = Scanner::getSignature(ENGINE_DLL_NAME, "55 8B EC 8B 0D ? ? ? ? 81 F9 ? ? ? ? 75 0C A1 ? ? ? ? 35 ? ? ? ? EB 05 8B 01 FF 50 34 50", { 0 }, 0, false, false);

  //VSTDLIB_DLL_NAME
  Offsets::signatures::interface_engine_cvar  = Scanner::getSignature(VSTDLIB_DLL_NAME, "8B 0D ? ? ? ? C7 05", { 2 });
  Offsets::signatures::convar_name_hash_table = Scanner::getSignature(VSTDLIB_DLL_NAME, "8B 3C 85", { 3 });
}

void Offsets::init(){
  initSignatures();
  initNetvars();
}