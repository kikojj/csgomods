#pragma once

#include <Windows.h>

#include "Client.hpp"
#include "Engine.hpp"

#include "Vector.hpp"

class RCS {
private:
  float _scale = 100.0f;
  Vector2 _newViewAngles;
  Vector2 _oldViewAngles;

  Memory* mem;

  Client* client = nullptr;
  Engine* engine = nullptr;

public:
  RCS(Memory*, Client*, Engine*);
  void loop(bool&);

  float scale();
  void scale(float v);
};