#pragma once

enum struct en_entity_quality: int {
  Invalid = -1,
  Normal,
  Genuine,
  Vintage,
  Unusual,
  Community = 5,
  Developer,
  SelftMade,
  Customized,
  Strange,
  Completed,
  Tournament = 12,
  InvalidLast
};