#include "square.hpp"

namespace abramov
{
  Square::Square(point_t p, double len):
  pLeftLower_(p), len_(len)
  {}

  double Square::getArea() const
  {
    return len_ * len_;
  }

  rectangle_t Square::getFrameRect() const
  {
    point_t pos;
    pos.x = pLeftLower_.x + len_ / 2;
    pos.y = pLeftLower_.y + len_ / 2;
    rectangle_t frame_rect;
    frame_rect.height = len_;
    frame_rect.width = len_;
    frame_rect.pos = pos;
    return frame_rect;
  }

  void Square::move(double dx, double dy)
  {
    pLeftLower_.x += dx;
    pLeftLower_.y += dy;
  }

  void Square::move(point_t p)
  {
    point_t center = getFrameRect().pos;
    double dx = p.x - center.x;
    double dy = p.y - center.y;
    move(dx, dy);
  }

  void Square::scale(double k)
  {
    len_ *= k;
    pLeftLower_.x += len_ / 2 * (k - 1);
    pLeftLower_.y += len_ / 2 * (k - 1);
  }
}
