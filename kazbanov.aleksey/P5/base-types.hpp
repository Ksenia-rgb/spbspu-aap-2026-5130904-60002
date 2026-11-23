#ifndef P5_BASE_TYPES_H
#define P5_BASE_TYPES_H

struct point_t {
  double x = 0.0;
  double y = 0.0;
};

struct rectangle_t {
  double width = 0.0;
  double height = 0.0;
  point_t pos;
};

#endif
