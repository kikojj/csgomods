#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

#include "BoneVector.hpp"
#include "../../Utils/BspParser/BspParser.hpp"

//////// VECTOR 2 ////////
struct s_vec2 {
  float x = 0.0f, y = 0.0f;
};
class c_vector2 {
public:
  float x;
  float y;

  c_vector2() {
    this->x = 0.0f;
    this->y = 0.0f;
  }
  c_vector2(float x, float y) {
    this->x = x;
    this->y = y;
  }
  c_vector2(s_vec2 vec) {
    this->x = vec.x;
    this->y = vec.y;
  }
  c_vector2(s_bone_vector vec) {
    this->x = vec.x;
    this->y = vec.y;
  }
  c_vector2(D3DXVECTOR2 vec) {
    this->x = vec.x;
    this->y = vec.y;
  }

  //operators
  float operator[](int xy) {
    return xy == 0 ? this->x :this->y;
  }
  c_vector2 operator+(c_vector2 vec) {
    return c_vector2(this->x + vec.x, this->y + vec.y);
  }
  c_vector2 operator-(c_vector2 vec) {
    return c_vector2(this->x - vec.x, this->y - vec.y);
  }
  c_vector2 operator*(float x) {
    return c_vector2(this->x * x, this->y * x);
  }
  void operator=(c_vector2 vec) {
    this->x = vec.x;
    this->y = vec.y;
  }
  friend bool operator==(const c_vector2& left, const c_vector2& right) {
    return left.x == right.x && left.y == right.y;
  }
  friend bool operator!=(const c_vector2& left, const c_vector2& right) {
    return !operator==(left, right);
  }
  friend std::ostream& operator<<(std::ostream& out, const c_vector2& vec) {
    out << vec.x << ", " << vec.y;
    return out;
  }

  //type cast
  s_vec2 to_vec2() {
    return s_vec2{ this->x, this->y };
  }

  D3DXVECTOR2 to_d3dx_vec2() {
    return D3DXVECTOR2{ this->x, this->y };
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

  bool is_zero() {
    return this->x == 0 && this->y == 0;
  }
};

//////// VECTOR 3 ////////
struct s_vec3 {
  float x = 0.0f, y = 0.0f, z = 0.0f;
};
class c_vector3 {
public:
  float x;
  float y;
  float z;

  c_vector3() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
  }
  c_vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  c_vector3(s_vec3 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
  }
  c_vector3(s_bone_vector vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
  }
  c_vector3(D3DXVECTOR3 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
  }

  //operators
  float operator[](int xyz) {
    return xyz == 0 ? this->x : xyz == 1 ? this->y : this->z;
  }
  c_vector3 operator+(c_vector3 vec) {
    return c_vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
  }
  c_vector3 operator-(c_vector3 vec) {
    return c_vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
  }
  c_vector3 operator*(float x) {
    return c_vector3(this->x * x, this->y * x, this->z * x);
  }
  void operator=(c_vector3 vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;
  }
  friend bool operator==(const c_vector3& left, const c_vector3& right) {
    return left.x == right.x && left.y == right.y && left.z == right.z;
  }
  friend bool operator!=(const c_vector3& left, const c_vector3& right) {
    return !operator==(left, right);
  }
  friend std::ostream& operator<<(std::ostream& out, const c_vector3& vec) {
    out << vec.x << ", " <<vec.y << ", " << vec.z;
    return out;
  }

  //type cast
  s_vec3 to_vec3() {
    return s_vec3{ this->x, this->y, this->z };
  }
  c_vector2 to_vector2() {
    return c_vector2(this->x, this->y);
  }
  D3DXVECTOR3 to_d3dx_vec3() {
    return D3DXVECTOR3{ this->x, this->y, this->z };
  }
  D3DXVECTOR2 to_d3dx_vec2() {
    return D3DXVECTOR2{ this->x, this->y };
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

  bool is_zero() {
    return this->x == 0 && this->y == 0 && this->z == 0;
  }
};