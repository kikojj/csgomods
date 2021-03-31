#pragma once

#include "../Scanner/Scanner.hpp"

namespace c_offsets {
  static struct netvars {
    static int m_armor_value;
    static int m_collision;
    static int m_collision_group;
    static int m_local;
    static int m_move_type;
    static int m_original_owner_xuid_high;
    static int m_original_owner_xuid_low;
    static int m_aim_punch_angle;
    static int m_aim_punch_angle_vel;
    static int m_b_gun_game_immunity;
    static int m_b_has_defuser;
    static int m_b_has_helmet;
    static int m_b_in_reload;
    static int m_b_is_defusing;
    static int m_b_is_scoped;
    static int m_b_spotted;
    static int m_b_spotted_by_mask;
    static int m_dw_bone_matrix;
    static int m_dw_in_game;
    static int m_f_accuracy_penalty;
    static int m_f_flags;
    static int m_f_fallback_wear;
    static int m_f_flash_duration;
    static int m_f_flash_max_alpha;
    static int m_f_flash_alpha;
    static int m_f_next_primary_attack;
    static int m_h_active_weapon;
    static int m_h_my_weapons;
    static int m_h_observer_target;
    static int m_h_owner;
    static int m_h_owner_entity;
    static int m_i_account_id;
    static int m_i_account;
    static int m_i_clip1;
    static int m_i_competitive_ranking;
    static int m_i_competitive_wins;
    static int m_i_ping;
    static int m_i_kills;
    static int m_i_assists;
    static int m_i_deaths;
    static int m_i_mvps;
    static int m_i_score;
    static int m_sz_clan;
    static int m_i_crosshair_id;
    static int m_i_entity_quality;
    static int m_i_fov_start;
    static int m_i_glow_index;
    static int m_i_health;
    static int m_h_view_model;
    static int m_i_view_model_index;
    static int m_n_model_index;
    static int m_i_item_definition_index;
    static int m_i_item_id_high;
    static int m_i_observer_mode;
    static int m_i_shots_fired;
    static int m_i_state;
    static int m_i_team_num;
    static int m_life_state;
    static int m_n_fallback_paint_kit;
    static int m_n_fallback_seed;
    static int m_n_fallback_stat_trak;
    static int m_i_default_fov;
    static int m_n_force_bone;
    static int m_n_tick_base;
    static int m_rgf_coordinate_frame;
    static int m_sz_custom_name;
    static int m_sz_last_place_name;
    static int m_vec3_origin;
    static int m_vec3_velocity;
    static int m_vec3_view_offset;
    static int m_view_punch_angle;
    static int m_third_person_view_angles;
    static int m_clr_render;
    static int m_f_c4_blow;
    static int m_f_timer_length;
    static int m_f_defuse_length;
    static int m_f_defuse_count_down;
    static int m_h_bomb_defuser;
    static int m_n_bomb_site;
    static int cs_gamerules_data;
    static int m_survival_rules;
    static int m_survival_game_rule_decision_types;
    static int m_b_is_valve_ds;
    static int m_b_freeze_period;
    static int m_b_warmup_period;
    static int m_b_bomb_planted;
    static int m_b_is_queued_matchmaking;
    static int m_f_simulation_time;
    static int m_f_lower_body_yaw_target;
    static int m_ang_eye_angles_x;
    static int m_ang_eye_angles_y;
    static int m_f_next_attack;
    static int m_i_most_recent_model_bone_counter;
    static int m_f_last_bone_setup_time;
    static int m_b_started_arming;
    static int m_b_use_custom_bloom_scale;
    static int m_b_use_custom_auto_exposure_min;
    static int m_b_use_custom_auto_exposure_max;
    static int m_f_custom_bloom_scale;
    static int m_f_custom_auto_exposure_min;
    static int m_f_custom_auto_exposure_max;
    static int m_h_weapon_world_model;
    static int m_b_dormant;
  } netvars;
  void init_netvars();

  static struct signatures {
    static int dw_model_precache;
    static int dw_client_state;
    static int dw_cs_get_local_player;
    static int dw_cs_is_hltv;
    static int dw_cs_map;
    static int dw_cs_map_directory;
    static int dw_cs_max_player;
    static int dw_cs_player_info;
    static int dw_cs_state;
    static int dw_cs_view_angles;
    static int dw_cs_delta_ticks;
    static int dw_cs_last_outgoing_command;
    static int dw_cs_choked_commands;
    static int dw_cs_net_channel;
    static int dw_entity_list;
    static int dw_force_attack;
    static int dw_force_attack2;
    static int dw_force_backward;
    static int dw_force_forward;
    static int dw_force_jump;
    static int dw_force_left;
    static int dw_force_right;
    static int dw_game_dir;
    static int dw_game_rules_proxy;
    static int dw_get_all_classes;
    static int dw_glow_object_manager;
    static int dw_input;
    static int dw_interface_link_list;
    static int dw_local_player;
    static int dw_mouse_enable;
    static int dw_mouse_enable_ptr;
    static int dw_player_resource;
    static int dw_radar_base;
    static int dw_sensitivity;
    static int dw_sensitivity_ptr;
    static int dw_set_clan_tag;
    static int dw_view_matrix;
    static int dw_weapon_table;
    static int dw_weapon_table_index;
    static int dw_yaw_ptr;
    static int dw_zoom_sensitivity_ratio_ptr;
    static int dw_send_packets;
    static int dw_p_direct_3d_device9;
    static int m_p_studio_hdr;
    static int m_yaw_class_ptr;
    static int m_pitch_class_ptr;
    static int interface_engine_cvar;
    static int convar_name_hash_table;
    static int model_ambient_min;
    static int set_abs_angles;
    static int set_abs_origin;
    static int is_c4_owner;
    static int force_update_spectator_glow;
    static int anim_overlays;
    static int m_f_spawntime;
    static int find_hud_element;

    //for steam overlay activated check
    static int overlay_activated1;
    //for steam overlay activated check
    static int overlay_activated2;

    //for autoaccept
    static int h_confirm_match;

    //for visible check
    static int dw_client_mode;
    //for visible check
    static int dw_trace_line;

    //for lineThroughSmoke
    static int dw_line_through_smoke;

    //for ClientCmd
    static int dw_client_cmd;

    //global vars
    static int dw_global_vars;
  } signatures;
  void init_signatures();

  void init();
};