#include "RCS.hpp"

RCS::RCS(Memory* mem, Client* client, Engine* engine): mem(mem), client(client), engine(engine) {
  _newViewAngles = Vector2(0.0f, 0.0f);
  _oldViewAngles = Vector2(0.0f, 0.0f);
}

void RCS::loop(bool& isAimWorking){
  _newViewAngles = engine->clientState->dwViewAngles();
  auto m_aimPunchAngle = client->localPlayer->m_aimPunchAngle();

  if (client->localPlayer->m_iShotsFired() > 1)
  {
    _newViewAngles.x -= (m_aimPunchAngle.x - (!isAimWorking ? _oldViewAngles.x : 0)) * (_scale * 0.02f);
    _newViewAngles.y -= (m_aimPunchAngle.y - (!isAimWorking ? _oldViewAngles.y : 0)) * (_scale * 0.02f);

    _newViewAngles.clamp();

    engine->clientState->dwViewAngles(_newViewAngles);
  }

  _oldViewAngles.x = m_aimPunchAngle.x;
  _oldViewAngles.y = m_aimPunchAngle.y;
}

float RCS::scale(){
  return this->_scale;
}

void RCS::scale(float v){
  if (v < 0.0f) {
    v = 0.0f;
  }
  if (v > 100.0f) {
    v = 100.0f;
  }
  _scale = v;
}
