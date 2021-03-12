#pragma once

class FlagsState {
public:
  static bool isOnGround(DWORD flags) {
    return flags & (1 << 0);
  }
  static bool isDucking(DWORD flags) {
    return flags & (1 << 1);
  }
  static bool isWaterJump(DWORD flags) {
    return flags & (1 << 2);
  }
  static bool isOnTrain(DWORD flags) {
    return flags & (1 << 3);
  }
  static bool isInRain(DWORD flags) {
    return flags & (1 << 4);
  }
  static bool isFrozen(DWORD flags) {
    return flags & (1 << 5);
  }
  static bool isAtControls(DWORD flags) {
    return flags & (1 << 6);
  }
  static bool isClient(DWORD flags) {
    return flags & (1 << 7);
  }
  static bool isFakeClient(DWORD flags) {
    return flags & (1 << 8);
  }
  static bool isInWater(DWORD flags) {
    return flags & (1 << 9);
  }
};