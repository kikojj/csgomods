#pragma once

class c_flags_state {
public:
  static bool is_on_ground(int flags) {
    return flags & (1 << 0);
  }
  static bool is_ducking(int flags) {
    return flags & (1 << 1);
  }
  static bool is_water_jump(int flags) {
    return flags & (1 << 2);
  }
  static bool is_on_train(int flags) {
    return flags & (1 << 3);
  }
  static bool is_in_rain(int flags) {
    return flags & (1 << 4);
  }
  static bool is_frozen(int flags) {
    return flags & (1 << 5);
  }
  static bool is_at_controls(int flags) {
    return flags & (1 << 6);
  }
  static bool is_client(int flags) {
    return flags & (1 << 7);
  }
  static bool is_fake_client(int flags) {
    return flags & (1 << 8);
  }
  static bool is_in_water(int flags) {
    return flags & (1 << 9);
  }
};