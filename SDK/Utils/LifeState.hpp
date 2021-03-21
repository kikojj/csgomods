#pragma once

enum LifeState{
  INVALID_LIFESTATE = -1,
  LIFESTATE_ALIVE = 0,// alive
  LIFESTATE_DYING = 1, // playing death animation or still falling off of a ledge waiting to hit ground
  LIFESTATE_DEAD = 2, // dead. lying still.
};