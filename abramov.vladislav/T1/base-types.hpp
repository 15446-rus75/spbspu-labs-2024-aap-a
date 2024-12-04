#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP
namespace abramov
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

  double getLength(point_t p1, point_t p2);
}
#endif
