#pragma once

#include <vector>

enum Skeleton {
  NEAREST = 0,

  NAVEL = 3,
  STOMACH = 4,
  CHEST = 6,
  NECK = 7,
  HEAD = 8,

  LEFT_SHOULDER = 11,
  LEFT_EBLOW = 12,
  LEFT_HAND = 13,

  RIGHT_SHOULDER = 41,
  RIGHT_EBLOW = 42,
  RIGHT_HAND = 43,

  LEFT_THIGH = 70,
  LEFT_KNEE = 71,
  LEFT_FOOT = 72,

  RIGHT_THIGH = 77,
  RIGHT_KNEE = 78,
  RIGHT_FOOT = 79,
};

static std::vector<Skeleton> ALL_BONES = {
    NAVEL,
    STOMACH,
    CHEST,
    NECK,
    HEAD,
    LEFT_SHOULDER,
    LEFT_EBLOW,
    LEFT_HAND,
    RIGHT_SHOULDER,
    RIGHT_EBLOW,
    RIGHT_HAND,
    LEFT_THIGH,
    LEFT_KNEE,
    LEFT_FOOT,
    RIGHT_THIGH,
    RIGHT_KNEE,
    RIGHT_FOOT
};

static std::vector<Skeleton> MAIN_BONES = {
    NAVEL,
    STOMACH,
    CHEST,
    NECK,
    HEAD,
};