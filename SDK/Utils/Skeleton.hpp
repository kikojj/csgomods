#pragma once

#include <vector>

enum struct en_skeleton: int {
  Nearest = 0,

  Navel = 3,
  Stomach = 4,
  Chest = 6,
  Neck = 7,
  Head = 8,

  LeftShoulder = 11,
  LeftEblow = 12,
  LeftHand = 13,

  RightShoulder = 41,
  RightEblow = 42,
  RightHand = 43,

  LeftThigh = 70,
  LeftKnee = 71,
  LeftFoot = 72,

  RightThigh = 77,
  RightKnee = 78,
  RightFoot = 79,
};

static const std::vector<en_skeleton> ALL_BONES = {
    en_skeleton::Navel,
    en_skeleton::Stomach,
    en_skeleton::Chest,
    en_skeleton::Neck,
    en_skeleton::Head,
    en_skeleton::LeftShoulder,
    en_skeleton::LeftEblow,
    en_skeleton::LeftHand,
    en_skeleton::RightShoulder,
    en_skeleton::RightEblow,
    en_skeleton::RightHand,
    en_skeleton::LeftThigh,
    en_skeleton::LeftKnee,
    en_skeleton::LeftFoot,
    en_skeleton::RightThigh,
    en_skeleton::RightKnee,
    en_skeleton::RightFoot
};

static const std::vector<en_skeleton> MAIN_BONES = {
    en_skeleton::Navel,
    en_skeleton::Stomach,
    en_skeleton::Chest,
    en_skeleton::Neck,
    en_skeleton::Head,
};