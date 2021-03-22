#pragma once

#include <vector>

enum struct Skeleton : int {
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
    Skeleton::NAVEL,
    Skeleton::STOMACH,
    Skeleton::CHEST,
    Skeleton::NECK,
    Skeleton::HEAD,
    Skeleton::LEFT_SHOULDER,
    Skeleton::LEFT_EBLOW,
    Skeleton::LEFT_HAND,
    Skeleton::RIGHT_SHOULDER,
    Skeleton::RIGHT_EBLOW,
    Skeleton::RIGHT_HAND,
    Skeleton::LEFT_THIGH,
    Skeleton::LEFT_KNEE,
    Skeleton::LEFT_FOOT,
    Skeleton::RIGHT_THIGH,
    Skeleton::RIGHT_KNEE,
    Skeleton::RIGHT_FOOT
};

static std::vector<Skeleton> MAIN_BONES = {
    Skeleton::NAVEL,
    Skeleton::STOMACH,
    Skeleton::CHEST,
    Skeleton::NECK,
    Skeleton::HEAD,
};