#pragma once

#include <iostream>

#include "BoneVector.hpp"
#include "../../Utils/BspParser/BspParser.hpp"

//////// VECTOR 2 ////////

struct Vec2 {
  float x = 0.0f, y = 0.0f;
};

class Vector2 {
public:
  float x;
  float y;

  Vector2() {
    this->x = 0.0f;
    this->y = 0.0f;
  }
  Vector2(float x, float y) {
    this->x = x;
    this->y = y;
  }
  Vector2(Vec2 vec) {
    this->x = vec.x;
    this->y = vec.y;
  }
  Vector2(BoneVector vec) {
    this->x = vec.x;
    this->y = vec.y;
  }

  //operators
  float operator[](int xy) {
    return xy == 0 ? this->x :this->y;
  }
  Vector2 operator+(Vector2 vec) {
    return Vector2(this->x + vec.x, this->y + vec.y);
  }
  Vector2 operator-(Vector2 vec) {
    return Vector2(this->x - vec.x, this->y - vec.y);
  }
  Vector2 operator*(float x) {
    return Vector2(this->x * x, this->y * x);
  }
  void operator=(Vector2 vec) {
    this->x = vec.x;
    this->y = vec.y;
  }
  friend bool operator==(const Vector2& left, const Vector2& right) {
    return left.x == right.x && left.y == right.y;
  }
  friend bool operator!=(const Vector2& left, const Vector2& right) {
    return !operator==(left, right);
  }
  friend std::ostream& operator<<(std::ostream& out, const Vector2& vec) {
    out << vec.x << ", " << vec.y;
    return out;
  }

  //type cast
  Vec2 toVec2() {
    return Vec2{ this->x, this->y };
  }

  //features
  void normalize() {
    while (this->x > 89.0f) {
      this->x -= 180.f;
    }

    while (this->x < -89.0f) {
      this->x += 180.f;
    }

    while (this->y > 180.f) {
      this->y -= 360.f;
    }

    while (this->y < -180.f) {
      this->y += 360.f;
    }
  }

  void clamp() {
    if (this->x > 89.0f) {
      this->x = 89.0f;
    }

    if (this->x < -89.0f) {
      this->x = -89.0f;
    }

    while (this->y > 180) {
      this->y -= 360;
    }

    while (this->y < -180) {
      this->y += 360;
    }
  }

  bool isZero() {
    return this->x == 0 && this->y == 0;
  }
};

//////// VECTOR 3 ////////

struct Vec3 {
  float x = 0.0f, y = 0.0f, z = 0.0f;
};

class Vector3 {
public:
  float x;
  float y;
  float z;

  Vector3() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
  }
  Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  Vector3(Vec3 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
  }
  Vector3(BoneVector vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
  }

  //operators
  float operator[](int xyz) {
    return xyz == 0 ? this->x : xyz == 1 ? this->y : this->z;
  }
  Vector3 operator+(Vector3 vec) {
    return Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
  }
  Vector3 operator-(Vector3 vec) {
    return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
  }
  Vector3 operator*(float x) {
    return Vector3(this->x * x, this->y * x, this->z * x);
  }
  void operator=(Vector3 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
  }
  friend bool operator==(const Vector3& left, const Vector3& right) {
    return left.x == right.x && left.y == right.y && left.z == right.z;
  }
  friend bool operator!=(const Vector3& left, const Vector3& right) {
    return !operator==(left, right);
  }
  friend std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
    out << vec.x << ", " <<vec.y << ", " << vec.z;
    return out;
  }

  //type cast
  Vec3 toVec3() {
    return Vec3{ this->x, this->y, this->z };
  }
  Vector2 toVector2() {
    return Vector2(this->x, this->y);
  }

  rn::detail::matrix_t<3, 1> toMatrix() {
    return rn::detail::matrix_t<3, 1>(this->x, this->y, this->z);
  }


  //features
  void normalize() {
    while (this->x > 89.0f) {
      this->x -= 180.f;
    }

    while (this->x < -89.0f) {
      this->x += 180.f;
    }

    while (this->y > 180.f) {
      this->y -= 360.f;
    }

    while (this->y < -180.f) {
      this->y += 360.f;
    }
  }

  void clamp() {
    if (this->x > 89.0f) {
      this->x = 89.0f;
    }

    if (this->x < -89.0f) {
      this->x = -89.0f;
    }

    while (this->y > 180) {
      this->y -= 360;
    }

    while (this->y < -180) {
      this->y += 360;
    }
    
    if (this->z != 0) {
      this->z = 0;
    }
  }

  bool isZero() {
    return this->x == 0 && this->y == 0 && this->z == 0;
  }
};