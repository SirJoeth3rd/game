class vec2d {
public:
  float x, y;
  
  vec2d(float x, float y): x(x), y(y) {};
  vec2d(): x(0), y(0) {};
  
  vec2d operator+(const vec2d& v);
  vec2d operator*(const int scale);
};
