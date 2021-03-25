#pragma once

#include "../Scanner/Scanner.hpp"

namespace Offsets {
  static struct netvars {
    static int m_ArmorValue;
    static int m_Collision;
    static int m_CollisionGroup;
    static int m_Local;
    static int m_MoveType;
    static int m_OriginalOwnerXuidHigh;
    static int m_OriginalOwnerXuidLow;
    static int m_aimPunchAngle;
    static int m_aimPunchAngleVel;
    static int m_bGunGameImmunity;
    static int m_bHasDefuser;
    static int m_bHasHelmet;
    static int m_bInReload;
    static int m_bIsDefusing;
    static int m_bIsScoped;
    static int m_bSpotted;
    static int m_bSpottedByMask;
    static int m_dwBoneMatrix;
    static int m_dwInGame;
    static int m_fAccuracyPenalty;
    static int m_fFlags;
    static int m_flFallbackWear;
    static int m_flFlashDuration;
    static int m_flFlashMaxAlpha;
    static int m_flFlashAlpha;
    static int m_flNextPrimaryAttack;
    static int m_hActiveWeapon;
    static int m_hMyWeapons;
    static int m_hObserverTarget;
    static int m_hOwner;
    static int m_hOwnerEntity;
    static int m_iAccountID;
    static int m_iClip1;
    static int m_iCompetitiveRanking;
    static int m_iCompetitiveWins;
    static int m_iCrosshairId;
    static int m_iEntityQuality;
    static int m_iFOVStart;
    static int m_iGlowIndex;
    static int m_iHealth;
    static int m_hViewModel;
    static int m_iViewModelIndex;
    static int m_nModelIndex;
    static int m_iItemDefinitionIndex;
    static int m_iItemIDHigh;
    static int m_iObserverMode;
    static int m_iShotsFired;
    static int m_iState;
    static int m_iTeamNum;
    static int m_lifeState;
    static int m_nFallbackPaintKit;
    static int m_nFallbackSeed;
    static int m_nFallbackStatTrak;
    static int m_iDefaultFOV;
    static int m_nForceBone;
    static int m_nTickBase;
    static int m_rgflCoordinateFrame;
    static int m_szCustomName;
    static int m_szLastPlaceName;
    static int m_vecOrigin;
    static int m_vecVelocity;
    static int m_vecViewOffset;
    static int m_viewPunchAngle;
    static int m_thirdPersonViewAngles;
    static int m_clrRender;
    static int m_flC4Blow;
    static int m_flTimerLength;
    static int m_flDefuseLength;
    static int m_flDefuseCountDown;
    static int m_hBombDefuser;
    static int m_nBombSite;
    static int cs_gamerules_data;
    static int m_SurvivalRules;
    static int m_SurvivalGameRuleDecisionTypes;
    static int m_bIsValveDS;
    static int m_bFreezePeriod;
    static int m_bWarmupPeriod;
    static int m_bBombPlanted;
    static int m_bIsQueuedMatchmaking;
    static int m_flSimulationTime;
    static int m_flLowerBodyYawTarget;
    static int m_angEyeAnglesX;
    static int m_angEyeAnglesY;
    static int m_flNextAttack;
    static int m_iMostRecentModelBoneCounter;
    static int m_flLastBoneSetupTime;
    static int m_bStartedArming;
    static int m_bUseCustomBloomScale;
    static int m_bUseCustomAutoExposureMin;
    static int m_bUseCustomAutoExposureMax;
    static int m_flCustomBloomScale;
    static int m_flCustomAutoExposureMin;
    static int m_flCustomAutoExposureMax;
    static int m_hWeaponWorldModel;
    static int m_bDormant;
  } netvars;
  void initNetvars();

  static struct signatures {
    static int dwClientState;
    static int dwModelPrecache;
    static int dwClientState_GetLocalPlayer;
    static int dwClientState_IsHLTV;
    static int dwClientState_Map;
    static int dwClientState_MapDirectory;
    static int dwClientState_MaxPlayer;
    static int dwClientState_PlayerInfo;
    static int dwClientState_State;
    static int dwClientState_ViewAngles;
    static int clientstate_delta_ticks;
    static int clientstate_last_outgoing_command;
    static int clientstate_choked_commands;
    static int clientstate_net_channel;
    static int dwEntityList;
    static int dwForceAttack;
    static int dwForceAttack2;
    static int dwForceBackward;
    static int dwForceForward;
    static int dwForceJump;
    static int dwForceLeft;
    static int dwForceRight;
    static int dwGameDir;
    static int dwGameRulesProxy;
    static int dwGetAllClasses;
    static int dwGlowObjectManager;
    static int dwInput;
    static int dwInterfaceLinkList;
    static int dwLocalPlayer;
    static int dwMouseEnable;
    static int dwMouseEnablePtr;
    static int dwPlayerResource;
    static int dwRadarBase;
    static int dwSensitivity;
    static int dwSensitivityPtr;
    static int dwSetClanTag;
    static int dwViewMatrix;
    static int dwWeaponTable;
    static int dwWeaponTableIndex;
    static int dwYawPtr;
    static int dwZoomSensitivityRatioPtr;
    static int dwbSendPackets;
    static int dwppDirect3DDevice9;
    static int m_pStudioHdr;
    static int m_yawClassPtr;
    static int m_pitchClassPtr;
    static int interface_engine_cvar;
    static int convar_name_hash_table;
    static int model_ambient_min;
    static int set_abs_angles;
    static int set_abs_origin;
    static int is_c4_owner;
    static int force_update_spectator_glow;
    static int anim_overlays;
    static int m_flSpawnTime;
    static int find_hud_element;

    //for steam overlay activated check
    static int overlayActivated1;
    //for steam overlay activated check
    static int overlayActivated2;

    //for autoaccept
    static int hConfirmMatch;

    //for visible check
    static int dwClientMode;
    //for visible check
    static int dwTraceLine;

    //for lineThroughSmoke
    static int dwLineThroughSmoke;

    //for ClientCmd_Unrestricted
    static int dwClientCmdUD;

    //global vars
    static int dwGlobalVars;

    //rank reveal
    static int dwRankReveal;

  } signatures;
  void initSignatures();

  void init();
};