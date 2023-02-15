#include "vec2d.hpp"

vec2d vec2d::operator+(const vec2d& v) {
  return vec2d(x + v.x, y + v.y);
}

vec2d vec2d::operator*(const int scale) {
  return vec2d(x*scale, y*scale);
}
