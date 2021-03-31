#pragma once

enum struct en_life_state: int {
  Invalid = -1,
  Alive = 0,    // alive
  Dying = 1,    // playing death animation or still falling off of a ledge waiting to hit ground
  Dead = 2,     // dead. lying still.
  InvalidLast
};